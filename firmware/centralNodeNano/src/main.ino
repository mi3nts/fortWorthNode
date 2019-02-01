#include <Arduino.h>
#include <Wire.h>


#include <devicesMints.h>
#include <jobsMints.h>



bool PPD42NSOnline;
uint8_t PPD42NSPin = 10;

bool    LIBRADOnline;
uint8_t LIBRADPin   = 2;
long    LIBRADCount = 0;

void setup() {
  initializeSerialMints();
  delay(1000);
  PPD42NSOnline = initializePPD42NSMints();
  delay(1000);
  LIBRADOnline  = initializeLIBRADMints();
  delay(1000);
}

// the loop routine runs over and over again forever:
void loop() {

  if(PPD42NSOnline)
      {
        readPPD42NSMints(5);
      }

  if(LIBRADOnline)
      {
        readLIBRADMints(5);
      }

}
