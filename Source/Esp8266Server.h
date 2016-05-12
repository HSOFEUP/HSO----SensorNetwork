/*
  Esp8266.h - Library for wifi connection.
  Created by HSO, March 10, 2016.
  Released into the public domain.
*/

#ifndef ESP8266_SERVER_H
#define ESP8266_SERVER_H

#include "Esp8266WebTemplate.h"

namespace WIFI
{
  class Esp8266Server
  {
    public:
       // Config AP
       // @param - Sssid, passwd, channel, encryption type
       // @return - bool with op result
       static bool
       ConfigAP(String ssid, String pwd, int chl, WifiEncryption encrypt, SerialDriver::SerialPort * m_serial)
       {
        // Send cwmode command
        Esp8266Utils::SendAtCommand(cmd_cwsap, "\"" + ssid + "\",\"" + pwd + "\"," + String(chl) + "," + String(encrypt), tplt_ok, dbg_msg_ok, dbg_msg_not_ok, m_serial);
      }

     // Start Server
     // @param - Server mode and port
     // @return - bool with op result
     static bool
     StartServer(ServerMode mode, int port, SerialDriver::SerialPort * m_serial)
     {
      // Send cipserver command
      Esp8266Utils::SendAtCommand(cmd_cipserver, String(mode) + "," + String(port) , tplt_ok, dbg_msg_ok, dbg_msg_not_ok, m_serial);
     }

     // Stop Server
     // @param - Server mode 
     // @return - bool with op result
     static bool
     StopServer(ServerMode mode, SerialDriver::SerialPort * m_serial)
     {
      // Send cipserver command
      Esp8266Utils::SendAtCommand(cmd_cipserver, String(mode), tplt_ok, dbg_msg_ok, dbg_msg_not_ok, m_serial);
     }

     // Wait for http request
     // @param - serial port handler
     // @return - string with connection id
     static void
     WaitHttpRequest(int chars_to_read, HttpRequest * http, SerialDriver::SerialPort * m_serial)
     {
      // Debug output 
      m_serial->SerialWrite("Wait http request: ");
      
      String template_ipd = Esp8266Utils::ReadFromFlash(tplt_ipd);

      // Wait for connection
      long previousMillis = 0;
      previousMillis = millis();
      while((millis() - previousMillis) < 10000)
      {
        http->Ipd = m_serial->SoftwareSerialFilterRead(5000, (char*)template_ipd.c_str(), chars_to_read);
        
        // Check if there is any request
        if (http->Ipd.length() > 0)
        {
          // Debug output
          m_serial->SerialWrite("Received Ipd: ");  
          m_serial->SerialWrite(http->Ipd);
          
          // Delay 0.5s to receive all the http request
          //delay(50);

          // Extract connection Id
          String id = (String)Esp8266Utils::ExtractId(http->Ipd);
          if (id.length() <= 0)
          {
            continue;
          }
          else
          {
            http->Id = id;
            break;
          }
        }
        delay(1000);
      }
     }

    static bool
    SendWebPage(const char * web_page, SerialDriver::SerialPort * m_serial)
    {
      HttpRequest http;
      
      // Wait for connection
      while (http.Id.length() <= 0 || http.Ipd.length() <= 0)
        WaitHttpRequest(15, &http, m_serial);
        
      m_serial->SerialWrite("Id: " + http.Id);
      m_serial->SerialWrite("Ipd: " + http.Ipd);
      
      SendWebPage(http.Id, web_page, m_serial);
    }

    static bool
    SendWebPage(String Id, const char * web_page, SerialDriver::SerialPort * m_serial)
    {
      // Debug output 
      m_serial->SerialWrite("Send web page: ");
      
      bool qos = false;
      
      while (!qos)
      {        
        // Send config webpage
        int len = strlen_P(web_page);
        int read_divisor = 50;
        for (int i = 0; i <= len / read_divisor; i++)
        {
          String webpage = Esp8266Utils::ReadFromFlash(web_page, i, read_divisor);
          qos = Esp8266Utils::SendData(Id, webpage, m_serial);
          if (!qos)
            break;
        }
        // If not delivered, repeat
        if (!qos)
          continue;
          
        // Close connection
        Esp8266Utils::SendAtCommand(cmd_cipclose, Id, tplt_ok, dbg_msg_ok, dbg_msg_not_ok, m_serial);
      }

      return qos;
    }

    // Wait for parameters to start client
    // @param - serial port handler
    // @return - bool with op result
    static bool
    ReceiveClientParameters(ClientParameters * client_parameters, SerialDriver::SerialPort * m_serial)
    {      
      // Debug output 
      m_serial->SerialWrite("Receive client parameters: ");
      
      HttpRequest http;
                           
      // Wait for connection
      while (http.Ipd.indexOf("favicon") != -1 || (http.Ipd.indexOf("SSID") == -1 || http.Ipd.indexOf("PSSWD") == -1 || http.Ipd.indexOf("NID") == -1 ||http.Ipd.indexOf("SIP") == -1))
        WaitHttpRequest(120, &http, m_serial);
        
      // Debug output 
      //m_serial->SerialWrite(http.Ipd);

      // +IPD,1,469:GET /config?SSID=Vodafone&PSSWD=teste&NID=room1 HTTP/1.1

      client_parameters->Ssid = http.Ipd.substring(http.Ipd.indexOf("SSID=") + 5 , http.Ipd.indexOf("&"));
      client_parameters->Password = http.Ipd.substring(http.Ipd.indexOf("PSSWD=") + 6 , http.Ipd.indexOf("&", http.Ipd.indexOf("PSSWD=")));
      client_parameters->HouseName = http.Ipd.substring(http.Ipd.indexOf("HID=") + 4 , http.Ipd.indexOf("&", http.Ipd.indexOf("HID=")));
      client_parameters->NodeName = http.Ipd.substring(http.Ipd.indexOf("NID=") + 4 , http.Ipd.indexOf("&", http.Ipd.indexOf("NID=")));
      client_parameters->ServerIp = http.Ipd.substring(http.Ipd.indexOf("SIP=") + 4 , http.Ipd.indexOf(" ", http.Ipd.indexOf("SIP=")));    

      if (client_parameters->Ssid.length() > 0 && 
          client_parameters->Password.length() > 0 && 
          client_parameters->HouseName.length() > 0 && 
          client_parameters->NodeName.length() > 0 && 
          client_parameters->ServerIp.length() > 0)
      {
        // Send success page
        SendWebPage(http.Id, SuccessPage, m_serial);     
        return true;
      }
    }
    private:
  };
}

#endif

