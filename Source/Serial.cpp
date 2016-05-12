#include "Serial.h"

namespace SerialDriver
{
  SerialPort::SerialPort()
  {
  }

  SerialPort::~SerialPort()
  {
  }
    
  void
  SerialPort::SetupSerial(long int BaudRate)
  {
    Serial.begin(BaudRate);
  }

  void
  SerialPort::SetupSoftwareSerial(uint8_t RX, uint8_t TX, uint16_t BAUDRATE)
  {
    m_serial = new SoftwareSerial(RX, TX);
    m_serial->begin(BAUDRATE);
  }

  void
  SerialPort::SerialWrite(String msg)
  {
    Serial.println("* " + m_driver_name + ": " + msg);
  }

  void
  SerialPort::SoftwareSerialWrite(String msg)
  {
    m_serial->print(msg);
  }
  
  String
  SerialPort::SoftwareSerialRead(int timeout)
  {
    long previousMillis = 0;
    String buffer       = "";
    char character;
     
    previousMillis = millis();
    while((millis() - previousMillis) < timeout)
    {
      while (m_serial->available()) 
      {
        character = m_serial->read();

        // Filter non ASCII characters
        if (character > 0 && character < 128)
          buffer += character;
      }
      previousMillis = millis();
    }
    return buffer;
  }

  String
  SerialPort::SoftwareSerialFilterRead(int timeout, char * tmplt, int number_chars)
  {
    long previousMillis = 0;
    String buffer       = "";
    char character;
     
    previousMillis = millis();
    if (SoftwareSerialFind(timeout, tmplt))
    {
       buffer += tmplt;
       while (buffer.length() < number_chars && (millis() - previousMillis) < timeout)
      {
        character = m_serial->read();

        // Filter non ASCII characters
        if (character > 0 && character < 128)
        {
          buffer += character;
          previousMillis = millis();
        }
      }
    }

    return buffer;
  }

  bool
  SerialPort::SoftwareSerialFind(int timeout, char * tmplt)
  {
    m_serial->setTimeout(timeout);
    return m_serial->find(tmplt);
  }

  void
  SerialPort::SetDriverName(String name)
  {
    m_driver_name = name;
  }
    
  void
  SerialPort::CommandLineDebug()
  {
    while(true)
    {
      while (m_serial->available()) 
      {
        Serial.print(m_serial->readString());
      }
      while (Serial.available()) 
      {
        m_serial->print(Serial.readString());
      }
    }
  }
}


