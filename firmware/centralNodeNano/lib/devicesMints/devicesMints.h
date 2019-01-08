#ifndef DEVICES_MINTS_H
#define DEVICES_MINTS_H

#include <Arduino.h>
// #include <Time.h>
#include "jobsMints.h"

#define CONV_FACTOR 0.00812

// For HTU21D
extern uint8_t PPD42NSPin;
bool initializePPD42NSMints();
void readPPD42NSMints(uint8_t sampleTimeSeconds);

extern uint8_t LIBRadPin;
extern long    LIBRadCount;
bool initializeLIBRadMints();
void countPulseLIBRadMints();
void readLIBRadMints(uint8_t sampleTimeSeconds);


// void sendCommand2DevicesMints(String command);
//
// void setTimeMints(String command);
// void printTimeMints();
// void printTimeOnlyMints();
//
// extern bool serialOut;






// // For HTU21D
// extern Adafruit_HTU21DF htu;
// bool initializeHTU21DMints();
// void readHTU21DMints();
//
// extern Adafruit_BMP280 bme;
// bool initializeBMP280Mints();
// void readBMP280Mints();
//
// extern OPCN3Mints opc;
// bool initializeOPCN3Mints();
// void readOPCN3Mints();

// void printInput(String command);
// void sensorPrintMints(String sensor,String readigs[],uint8_t numOfvals);




















#endif
