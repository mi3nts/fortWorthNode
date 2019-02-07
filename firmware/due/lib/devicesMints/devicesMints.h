#ifndef DEVICES_MINTS_H
#define DEVICES_MINTS_H

#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP280.h>
#include "Seeed_BME280.h"
#include <Adafruit_INA219.h>
#include "OPCN3Mints.h"
#include "MutichannelGasSensor.h"
#include "SparkFun_SCD30_Arduino_Library.h"
#include "jobsMints.h"





// void sendCommand2DevicesMints(String command);
//
// void setTimeMints(String command);
// void printTimeMints();
// void printTimeOnlyMints();
//
// extern bool serialOut;

// For HTU21D
extern Adafruit_HTU21DF htu;
bool initializeHTU21DMints();
void readHTU21DMints();

extern Adafruit_BMP280 bmp;
bool initializeBMP280Mints();
void readBMP280Mints();

extern BME280 bme280;
bool initializeBME280Mints();
void readBME280Mints();

bool initializeMGS001Mints();
void readMGS001Mints();

extern SCD30 scd;
bool initializeSCD30Mints();
void readSCD30Mints();


extern OPCN3Mints opc;
bool initializeOPCN3Mints();
void readOPCN3Mints();

extern Adafruit_INA219 ina;
bool initializeINA219Mints();
void readINA219Mints();


// void printInput(String command);
// void sensorPrintMints(String sensor,String readigs[],uint8_t numOfvals);




















#endif
