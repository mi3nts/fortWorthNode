//
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP280.h>
#include "Seeed_BME280.h"
#include <Wire.h>


#include <Adafruit_INA219.h>
#include "OPCN3Mints.h"

#include "OPCN3Mints.h"
// #include <Adafruit_INA219.h>
// #include "OPCN3Mints.h"



#include "devicesMints.h"
#include "jobsMints.h"


//





bool BME280Online;
BME280 bme280; // I2C
//
// bool BMP280Online;
// Adafruit_BMP280 bmp;
//
// bool HTU21DOnline;
// Adafruit_HTU21DF htu = Adafruit_HTU21DF();


//
// bool  INA219Online;
// Adafruit_INA219 ina;
// uint32_t currentFrequency;


#define CS 10
bool  OPCN3Online;
OPCN3Mints opc = OPCN3Mints(CS);

//
// // bool serialOut = true;
//

//

uint16_t sensingPeriod = 1000;

// String inputString = "";         // a String to hold incoming data
// // bool stringComplete = false;  // whether the string is complete
//
//



void setup() {

  initializeSerialMints();
  delay(1000);
  initializeSerialUSBMints();

  delay(1000);
  BME280Online = initializeBME280Mints();
  delay(1000);
  // BMP280Online = initializeBMP280Mints();
  // HTU21DOnline = initializeHTU21DMints();
  // delay(500);
  // INA219Online = initializeINA219Mints();
  // delay(1000);
  OPCN3Online =  initializeOPCN3Mints();
  delay(1500);


}


// the loop routine runs over and over again forever:
void loop() {

    delay(sensingPeriod);
    if(BME280Online)
    {
      readBME280Mints();
    }

    // delay(sensingPeriod);
    // if(HTU21DOnline)
    // {
    //   readHTU21DMints();
    // }
    //
    // delay(sensingPeriod);
    // if(BMP280Online)
    // {
    //   readBMP280Mints();
    // }

    delay(sensingPeriod);
    if(OPCN3Online)
    {
      readOPCN3Mints();
    }


   // delay(1000);
   //
  // if(INA219Online)
  // {
  //   readINA219Mints();
  // }

}



//
