#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Esp8266.h"
#include "MQ2.h"
#include "DHT.h"

#define DHTPIN 5     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22     // DHT 22 (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

WIFI::Esp8266 * esp8266;
MQ2DRIVER::MQ2  mq2;
DHT             dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  esp8266 = new WIFI::Esp8266();
  esp8266->Setup();

  mq2.setup();
  Serial.begin(57600);
}

void loop() {
  // Get data from MQ2 sensor
  float smoke_level = mq2.getGasLevel();

  // Wait a few seconds between measurements.
  //delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  esp8266->SendNodeData(smoke_level, h, t, hic);

  // Wait one hour between measurements
  long previousMillis = 0;
  previousMillis = millis();
  while((millis() - previousMillis) < 3600000);
}

