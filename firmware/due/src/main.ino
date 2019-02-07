//
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP280.h>

#include "Seeed_BME280.h"
#include <Adafruit_INA219.h>
#include "MutichannelGasSensor.h"
#include "SparkFun_SCD30_Arduino_Library.h"
#include "OPCN3Mints.h"

#include "devicesMints.h"
#include "jobsMints.h"


bool BME280Online;
BME280 bme280; // I2C
//

bool MGS001Online;

//
bool SCD30Online;
SCD30 scd;

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

uint16_t sensingPeriod = 2120;

uint16_t initPeriod = 1500;
// String inputString = "";         // a String to hold incoming data
// // bool stringComplete = false;  // whether the string is complete
//
//



void setup() {

  delay(initPeriod);
  initializeSerialMints();

  delay(initPeriod);
  initializeSerialUSBMints();

  delay(initPeriod);
  BME280Online = initializeBME280Mints();

  delay(initPeriod);
  SCD30Online = initializeSCD30Mints();

  delay(initPeriod);
  MGS001Online =  initializeMGS001Mints();

  delay(initPeriod);
  OPCN3Online =  initializeOPCN3Mints();


  // delay(1000);
  // BMP280Online = initializeBMP280Mints();

  // delay(500);
  // HTU21DOnline = initializeHTU21DMints();

  // delay(1000);
  // INA219Online = initializeINA219Mints();


}


// the loop routine runs over and over again forever:
void loop() {

    delay(sensingPeriod);
    if(BME280Online)
    {
      readBME280Mints();
    }

    delay(sensingPeriod);
        if(SCD30Online)
    {
      readSCD30Mints();
    }



    delay(sensingPeriod);
    if(MGS001Online)
    {
      readMGS001Mints();
    }

    delay(sensingPeriod);
    if(OPCN3Online)
    {
      readOPCN3Mints();
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



   // delay(1000);
   //
  // if(INA219Online)
  // {
  //   readINA219Mints();
  // }
  //
  // float c;
  //
  // c = gas.measure_NH3();
  // Serial.print("The concentration of NH3 is ");
  // if(c>=0) Serial.print(c);
  // else Serial.print("invalid");
  // Serial.println(" ppm");
  //
  // c = gas.measure_CO();
  // Serial.print("The concentration of CO is ");
  // if(c>=0) Serial.print(c);
  // else Serial.print("invalid");
  // Serial.println(" ppm");
  //
  // c = gas.measure_NO2();
  // Serial.print("The concentration of NO2 is ");
  // if(c>=0) Serial.print(c);
  // else Serial.print("invalid");
  // Serial.println(" ppm");
  //
  // c = gas.measure_C3H8();
  // Serial.print("The concentration of C3H8 is ");
  // if(c>=0) Serial.print(c);
  // else Serial.print("invalid");
  // Serial.println(" ppm");
  //
  // c = gas.measure_C4H10();
  // Serial.print("The concentration of C4H10 is ");
  // if(c>=0) Serial.print(c);
  // else Serial.print("invalid");
  // Serial.println(" ppm");
  //
  // c = gas.measure_CH4();
  // Serial.print("The concentration of CH4 is ");
  // if(c>=0) Serial.print(c);
  // else Serial.print("invalid");
  // Serial.println(" ppm");
  //
  // c = gas.measure_H2();
  // Serial.print("The concentration of H2 is ");
  // if(c>=0) Serial.print(c);
  // else Serial.print("invalid");
  // Serial.println(" ppm");
  //
  // c = gas.measure_C2H5OH();
  // Serial.print("The concentration of C2H5OH is ");
  // if(c>=0) Serial.print(c);
  // else Serial.print("invalid");
  // Serial.println(" ppm");
  //
  // // Xadow.greenLed(LEDON);
  // // delay(500);
  // // Xadow.greenLed(LEDOFF);
  // // delay(500);
  // Serial.println("...");
  //
  //












}



//
