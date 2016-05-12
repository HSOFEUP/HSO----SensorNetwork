/*
  Serial.h - Library for serial connections management.
  Created by HSO, March 10, 2016.
  Released into the public domain.
*/

#ifndef SERIAL_H
#define SERIAL_H

#include "Arduino.h"
#include <SoftwareSerial.h>

namespace SerialDriver
{
  class SerialPort
  {
    public:
      // Constructor
      SerialPort();
      // Destructor
      ~SerialPort();

      // Setup serial interface with computer
      // @param - Baudrate
      // @return - none
      void
      SetupSerial(long int BaudRate);
      // Setup software serial with sensor
      // @param - Serial pins and baudrate
      // @return - none
      void
      SetupSoftwareSerial(uint8_t RX, uint8_t TX, uint16_t BUADRATE);
      // Write debug message to usb interface
      // @param - Message to send
      // @return - none
      void
      SerialWrite(String msg);
      // Write message from software serial port
      // @param - Message to send
      // @return - none
      void
      SoftwareSerialWrite(String msg);
      // Read message from software serial port
      // @param - Reading timeout
      // @return - String with message readed
      String
      SoftwareSerialRead(int timeout);
       // Read message from software serial port
      // @param - Reading timeout, template to filter message and number of chars to read
      // @return - String with message readed
      String
      SoftwareSerialFilterRead(int timeout, char * tmplt, int number_chars);
       // Find string message from software serial port
      // @param - Reading timeout, template to find
      // @return - true or false
      bool
      SoftwareSerialFind(int timeout, char * tmplt);
      // Set driver name for debug message
      // @param - Driver name
      // @return - none
      void
      SetDriverName(String name);
      
      // Function to be called on debug porpuse only
      void
      CommandLineDebug(void);
    
    private:
      // Driver name
      String m_driver_name;
      // Software serial ptr
      SoftwareSerial * m_serial;
  };
}

#endif


