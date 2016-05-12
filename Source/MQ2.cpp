/*
  MQ2.h - Library to manage MQ-2 device.
  Created by HSO, March 10, 2016.
  Released into the public domain.
*/

#include "MQ2.h"

namespace MQ2DRIVER
{
  void
  MQ2::setup()
  {
    //the smoke sensor will be an input to the arduino
    pinMode(sensorPin, INPUT);
  }
  
  float
  MQ2::getGasLevel()
  {
    //arduino reads the value from the smoke sensor [0 - 1023]
    smoke_level= analogRead(sensorPin); 
    
    //prints just for debugging purposes, to see what values the sensor is picking up
    //Serial.println(F(String(smoke_level)));
  
    return smoke_level;
  }
}


