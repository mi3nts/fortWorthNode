#ifndef JOBS_MINTS_H
#define JOBS_MINTS_H

#include <Arduino.h>
#include "devicesMints.h"


void initializeSerialMints();

extern bool stringComplete;
extern String inputString;
void commandReadMints();

void serialEvent();




#endif
