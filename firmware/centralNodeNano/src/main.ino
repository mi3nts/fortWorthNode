#include <Arduino.h>
#include <Wire.h>


#include <devicesMints.h>
#include <jobsMints.h>



bool PPD42NSOnline;
uint8_t PPD42NSPin = 10;

bool    LIBRadOnline;
uint8_t LIBRadPin   = 2;
long    LIBRadCount = 0;

void setup() {
  initializeSerialMints();
  delay(1000);
  PPD42NSOnline = initializePPD42NSMints();
  delay(1000);
  LIBRadOnline  = initializeLIBRadMints();
  delay(1000);
}

// the loop routine runs over and over again forever:
void loop() {

  if(PPD42NSOnline)
      {
        readPPD42NSMints(5);
      }

  if(LIBRadOnline)
      {
        readLIBRadMints(5);
      }

}
