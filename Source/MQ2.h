/*
  MQ2.h - Library to manage MQ-2 device.
  Created by HSO, March 10, 2016.
  Released into the public domain.
*/

#ifndef MQ2_h
#define MQ2_h

#include "Arduino.h"
#include <SoftwareSerial.h>

namespace MQ2DRIVER
{
  class MQ2
  {
   public:
     void
     setup(void);
     float
     getGasLevel(void);
   private:
    const uint8_t sensorPin = 0;
    float smoke_level;
  };
}

#endif

