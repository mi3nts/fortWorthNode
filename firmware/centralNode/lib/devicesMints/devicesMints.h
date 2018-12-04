#ifndef DEVICES_MINTS_H
#define DEVICES_MINTS_H

#include <Arduino.h>
#include <Adafruit_HTU21DF.h>


void initializeSerialMints();


extern Adafruit_HTU21DF htu;
void initializeHTU21DMints();
void readHTU21DMints();






#endif // ADAFRUIT_NEOPIXEL_H
