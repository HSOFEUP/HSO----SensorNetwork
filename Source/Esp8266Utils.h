/*
  Esp8266.h - Library for wifi connection.
  Created by HSO, March 10, 2016.
  Released into the public domain.
*/

#ifndef ESP8266_UTILS_H
#define ESP8266_UTILS_H

namespace WIFI
{
  class Esp8266Utils
  {
    public:
     static bool
     SendAtCommand(const char * cmd, String parameters, const char * tplt, const char * g_msg, const char * b_msg, SerialDriver::SerialPort * m_serial)
     {
        String command = ReadFromFlash(cmd);
      
        // Send reset command
        m_serial->SerialWrite(command + parameters);
        m_serial->SoftwareSerialWrite(command + parameters + "\r\n");
        
        String search_template = ReadFromFlash(tplt);
        String g_dbg_msg       = ReadFromFlash(g_msg);
        String b_dbg_msg       = ReadFromFlash(b_msg);
        
        // Check response and print
        return PrintDebugMessage(m_serial->SoftwareSerialFind(c_client_read_timeout, (char*)search_template.c_str()), g_dbg_msg, b_dbg_msg, m_serial);
     }
    
    // Check responses to commands and print debug message    
    static bool
    PrintDebugMessage(bool result, String true_msg, String false_msg, SerialDriver::SerialPort * m_serial)
    {
      // Check response and print debug message
      if (result)
      {
        m_serial->SerialWrite(true_msg);
        return true;
      }
      else
      {
        m_serial->SerialWrite(false_msg);
        return false;
      }
    }

    // Send data by TCP or UDP connection
    // @param - Connection id and data to send
    // @return - bool with op result
    static bool
    SendData(String id, String data, SerialDriver::SerialPort * m_serial)
    {
      // Debug output 
      m_serial->SerialWrite("Sending data: ");
      
      // Send cipsend command
      if (!SendAtCommand(cmd_cipsend, id + "," + String(data.length()), tplt_grt_thn, dbg_msg_grt_th, "", m_serial))
      return false;

      // Read templates from progmem
      String search_template = Esp8266Utils::ReadFromFlash(tplt_send_ok);
      String g_dbg_msg       = ReadFromFlash(dbg_msg_send_ok);
      String b_dbg_msg       = ReadFromFlash(dbg_msg_send_not_ok);

      // Send data
      m_serial->SoftwareSerialWrite(data);
      if (!PrintDebugMessage(m_serial->SoftwareSerialFind(500, (char*)search_template.c_str()), g_dbg_msg, b_dbg_msg, m_serial))
        return false;

      return true;
    }

    // Read from flash with progmem
    static String
    ReadFromFlash(const char * data, int index, int read_divisor)
    {
      String tmp;
      char myChar;
      int len = strlen_P(data);
      
      for (int k = 0; k < read_divisor; k++)
      {
        if ((k + read_divisor * index) < len)
        {
          myChar =  pgm_read_byte_near(data + k + read_divisor * index);
          tmp += myChar;
        }
      }
      return tmp;
    }

    static String
    ReadFromFlash(const char * data)
    {
      char myChar;
      String bfr;
      int len = strlen_P(data);
      
      for (int k = 0; k < len; k++)
      {
        myChar =  pgm_read_byte_near(data + k);
        bfr += myChar;
      }

      return bfr;
    }

    // Extract Id connection
    static char
    ExtractId(String http_request)
    {
      return http_request.charAt(5);
    }
    private:
  };
}

#endif
