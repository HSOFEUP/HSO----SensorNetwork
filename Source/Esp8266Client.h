/*
  Esp8266.h - Library for wifi connection.
  Created by Tiago Rodrigues, March 10, 2016.
  Released into the public domain.
*/

#ifndef ESP8266_CLIENT_H
#define ESP8266_CLIENT_H

namespace WIFI
{
  class Esp8266Client
  {
    public:
    static bool
    ConnectToAp(ClientParameters clt_param, SerialDriver::SerialPort * m_serial)
    {
      // Send cwjap command   
      //clt_param.Ssid     = "Vodafone-922C87";
      //clt_param.Password = "126FCA2CED";

      // Send cwjap command
      Esp8266Utils::SendAtCommand(cmd_cwjap, "\"" + clt_param.Ssid + "\",\"" + clt_param.Password + "\"", tplt_ok, dbg_msg_connected, dbg_msg_not_connected, m_serial);
    }

    static bool
    ConnectToServer(ClientParameters clt_param, SerialDriver::SerialPort * m_serial)
    {
      //clt_param.ServerIp = "94.60.71.188";
      // Send cipstart command
      return Esp8266Utils::SendAtCommand(cmd_cipstart, String(tcp_chl) + ",\"TCP\",\"" + clt_param.ServerIp + "\",80", tplt_ok, dbg_msg_ok, dbg_msg_not_ok, m_serial);
    }

    static bool
    GetHttpRequest(String cmd, SerialDriver::SerialPort * m_serial)
    {
      //String cmd = "GET http://" + clt_param.ServerIp + "/Core/IO/Receiver.php?house=" + clt_param.HouseName + "&room=" + clt_param.NodeName + "&smoke=500&humidity=100&temperature=40&heatindex=10\r\n\r\n";
      m_serial->SerialWrite(cmd);
      return Esp8266Utils::SendData(String(tcp_chl), cmd, m_serial); 
    }

    static bool
    PostHttpRequest()
    {
      // call cipsend - Esp8266Utils::SendData
      //POST /test/demo_form.asp HTTP/1.1
      //Host: w3schools.com
      //name1=value1&name2=value2      
    }

    private:
  };
}

#endif
