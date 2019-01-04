#ifndef DEVICES_MINTS_H
#define DEVICES_MINTS_H

#include <Arduino.h>
#include <Time.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP280.h>
#include "OPCN3Mints.h"


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

extern Adafruit_BMP280 bme;
bool initializeBMP280Mints();
void readBMP280Mints();

extern OPCN3Mints opc;
bool initializeOPCN3Mints();
void readOPCN3Mints();

// void printInput(String command);
// void sensorPrintMints(String sensor,String readigs[],uint8_t numOfvals);




















#endif
