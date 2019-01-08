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




#endif
