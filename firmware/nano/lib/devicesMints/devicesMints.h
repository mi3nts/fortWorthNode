#ifndef DEVICES_MINTS_H
#define DEVICES_MINTS_H

#include <Arduino.h>
// #include <Time.h>
// #include "Adafruit_Sensor.h"
#include "Adafruit_VEML6070.h"
#include "Adafruit_TSL2591.h"

#include "jobsMints.h"



#define CONV_FACTOR 0.00812

// For HTU21D
extern uint8_t PPD42NSPin;
bool initializePPD42NSMints();
void readPPD42NSMints(uint8_t sampleTimeSeconds);

extern uint8_t LIBRADPin;
extern long    LIBRADCount;
bool initializeLIBRADMints();
void countPulseLIBRADMint();
void readLIBRADMints(uint8_t sampleTimeSeconds);



extern Adafruit_VEML6070 veml;
bool initializeVEML6070Mints();
void readVEML6070Mints();


extern Adafruit_TSL2591 tsl;
bool initializeTSL2591Mints();
void readTSL2591Mints();
// Taken from:https://github.com/adafruit/Adafruit_TSL2591_Library/blob/master/examples/tsl2591/tsl2591.ino
void displayTSL2591DetailsMints(void);
void configureTSL2591Mints(void);
void advancedReadTSL2591Mnits(void);
// Ends functions taken from:https://github.com/adafruit/Adafruit_TSL2591_Library/blob/master/examples/tsl2591/tsl2591.ino




#endif
