#include <Arduino.h>
// #include <devicesMints.h>
#include <jobsMints.h>
// #include <Wire.h>
// #include <Adafruit_HTU21DF.h>
#include "OPCN3Mints.h"

// Adafruit_HTU21DF htu = Adafruit_HTU21DF();
// Adafruit_BMP280 bme;

#define CS 10

OPCN3Mints OPCN3(CS);


String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool OPCN3Online;


void setup() {

   initializeSerialMints();

   // initializeHTU21DMints();
   // initializeBMP280Mints();
   // inputString.reserve(200);
   // SerialUSB.begin(9600);

   OPCN3Online = OPCN3.initialize();
   if(OPCN3Online){
     Serial.println("OPC Initialized");
   }else{
          Serial.println("OPC Not Initialized");
   }

   // delay(5000);
}


// the loop routine runs over and over again forever:
void loop() {
     if(OPCN3Online)
     {
      delay(5000);
      OPCN3.readHistogramData();
      delay(5000);
      OPCN3.readPMData();
     }
}
