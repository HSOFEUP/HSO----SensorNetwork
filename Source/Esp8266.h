/*
  Esp8266.h - Library for wifi connection.
  Created by HSO, March 10, 2016.
  Released into the public domain.
*/

#ifndef ESP8266_H
#define ESP8266_H

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Serial.h"
//
#include "Esp8266Configurations.h"
#include "Esp8266Utils.h"
#include "Esp8266Server.h"
#include "Esp8266Client.h"
#include "Esp8266WebTemplate.h"

namespace WIFI
{          
  class Esp8266
  {
    public:
      // Constructor
      Esp8266(void);
      // Destructor
      ~Esp8266(void);

      // Initial setup 
      // 1 - Create webpage and get configurations
      // 2 - Work as node in a network
      // @param - none
      // @return - none
      void
      Setup(void);

      // Send node data to server
      // @param - Data
      // @return - bool with op result
      void
      SendNodeData(float smoke_level, float h, float t, float hic);
      
    private:     
      // Reset device
      // @param - none
      // @return - bool with op result
      bool
      Reset(void);
      // Set wifi mode
      // @param - Desired mode
      // @return - bool with op result
      bool
      ConfigWMode(WifiMode mode);
      // Config Connections
      // @param - Mode single/multiple
      // @return - bool with op result
      bool
      ConfigConnections(WifiConnections wconnect);
      // Config webserver
      // @param - none
      // @return - none
      void
      ConfigWebServer(void);
      // Config client
      // @param - none
      // @return - none
      void
      ConfigClient(void);
      
      // Serial class
      SerialDriver::SerialPort * m_serial;

      // Esp8266 client variables
      ClientParameters client_parameters;
  };
}

#endif

