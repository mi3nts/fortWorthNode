#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_Sensor.h>
// #include "Adafruit_VEML6070.h"
// #include "Adafruit_TSL2591.h"

#include <devicesMints.h>
#include <jobsMints.h>




bool    VEML6070Online;
Adafruit_VEML6070 veml = Adafruit_VEML6070();


bool    TSL2591Online;
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)

// bool PPD42NSOnline;
// uint8_t PPD42NSPin = 10;

bool    LIBRADOnline;
uint8_t LIBRADPin   = 2;
long    LIBRADCount = 0;

unsigned long initializationPeriod = 1500;
unsigned long sensingPeriod = 2038;

void setup() {
  initializeSerialMints();
  // delay(1000);
  // PPD42NSOnline = initializePPD42NSMints();
  delay(initializationPeriod);
  LIBRADOnline       = initializeLIBRADMints();
  delay(initializationPeriod);
  VEML6070Online     = initializeVEML6070Mints();
  delay(initializationPeriod);
  TSL2591Online      = initializeTSL2591Mints();


/////////////////////////////////////////
//
//   Serial.begin(9600);
//
//   Serial.println(F("Starting Adafruit TSL2591 Test!"));
//
//   if (tsl.begin())
//   {
//     Serial.println(F("Found a TSL2591 sensor"));
//   }
//   else
//   {
//     Serial.println(F("No sensor found ... check your wiring?"));
//     while (1);
//   }
//
//   /* Display some basic information on this sensor */
//   displaySensorDetails();
//
//   /* Configure the sensor */
//   configureSensor();
// //////////////////////////////////////////
//
//






}


// the loop routine runs over and over again forever:
void loop() {



//
//   Serial.print("UV light level: "); Serial.println(uv.readUV());
//   delay(1000);
//   // if(PPD42NSOnline)
//   //     {
//   //       readPPD42NSMints(5);
//   //     }
//
//   //simpleRead();
// advancedRead();
// // unifiedSensorAPIRead();
  delay(sensingPeriod);

  if(VEML6070Online)
    {
      readVEML6070Mints();
    }

  delay(sensingPeriod);

  if(TSL2591Online)
      {
        readTSL2591Mints();
      }

  if(LIBRADOnline)
      {
        readLIBRADMints(5);
      }
  Serial.println("-------------------------------------"+String(millis())+"-------------------------------------");

}
