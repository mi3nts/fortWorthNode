#include <Arduino.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>


#include <devicesMints.h>
#include <jobsMints.h>

// #include "OPCN3Mints.h"

// #include <Adafruit_INA219.h>

Adafruit_HTU21DF htu = Adafruit_HTU21DF();
Adafruit_BMP280 bme;

// Adafruit_INA219 ina219;
// uint32_t currentFrequency;

// bool serialOut = true;

// #define CS 10
// OPCN3Mints OPCN3(CS);
// String inputString = "";         // a String to hold incoming data
// bool stringComplete = false;  // whether the string is complete
// bool  OPCN3Online;
bool HTU21DOnline;
bool BMP280Online;

void setup() {

  initializeSerialMints();
  delay(1000);
  initializeSerialUSBMints();
  delay(1000);
  HTU21DOnline = initializeHTU21DMints();
  delay(1000);
  BMP280Online = initializeBMP280Mints();

}
 // OPCN3Online = OPCN3.initialize();

// the loop routine runs over and over again forever:
void loop() {


    if(HTU21DOnline)
    {
      readHTU21DMints();
    }

delay(2000);

    if(BMP280Online)
    {
      readBMP280Mints();
    }

delay(2000);
   // if(BMP280Online)
   //    {
   //       readBMP280Mints();
   //    }




      // delay(5000);
      // OPCN3.readPMData();
      //
   //   // // }
   //  float  lk = 12.2392;
   //  String lks = String(lk,4);
   //  Serial.println(lks);
   //  // String lkt = {"sskjfsf","fjfsadffg"};
   //  // sensorPrintMints("HTU21D",lkt,2);
   //
   // String ordinal[5] = { "first", "second", "third", "fourth", "fifth"};
   //
   //
   //  sensorPrintMints("String sensor",ordinal,5);

}



//
