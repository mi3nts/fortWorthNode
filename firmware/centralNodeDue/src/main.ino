#include <Arduino.h>
#include <devicesMints.h>
#include <jobsMints.h>
#include <Wire.h>
#include <Adafruit_HTU21DF.h>


Adafruit_HTU21DF htu = Adafruit_HTU21DF();
Adafruit_BMP280 bme;


String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete



void setup() {

   initializeSerialMints();
   initializeHTU21DMints();
   initializeBMP280Mints();
   inputString.reserve(200);
}


// the loop routine runs over and over again forever:
void loop() {

  commandReadMints();

  // if (stringComplete) {
  //   Serial.println(inputString);
  //   // clear the string:
  //   inputString = "";
  //   stringComplete = false;
  // }


  // while(Serial.available()>0){
  //   char value = Serial.read();
  //   Serial.println("Hello Mints");
  //   Serial.println(value);
  // }


}
