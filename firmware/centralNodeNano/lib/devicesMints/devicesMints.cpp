
#include "devicesMints.h"

// // PPD42NS ---------------------------------------
bool initializePPD42NSMints(){
    pinMode(PPD42NSPin,INPUT);
    delay(1);
    return true;
  }

void readPPD42NSMints(uint8_t sampleTimeSeconds)  {

    unsigned long duration;
    unsigned long starttime;
    unsigned long sampletime_ms = sampleTimeSeconds*1000;//sampe 30s ;
    unsigned long lowPulseOccupancy = 0;
    float ratio = 0;
    float concentration = 0;

    starttime = millis();

    while ((millis()-starttime) < sampletime_ms) {
        duration = pulseIn(PPD42NSPin, LOW);
        lowPulseOccupancy = lowPulseOccupancy + duration;
    }

    unsigned long timeSpent = millis()-starttime;
    ratio = lowPulseOccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    String readings[4] = { String(lowPulseOccupancy), String(concentration,4), String(ratio,4), String(timeSpent) };
    sensorPrintNanoMints("PPD42NS",readings,4);

}


// // LIBRad ---------------------------------------

bool initializeLIBRADMints(){
    pinMode(LIBRADPin, INPUT);
    digitalWrite(LIBRADPin,HIGH);
    delay(1);
    return true;
  }

void countPulseLIBRADMints(){

      detachInterrupt(0);
      LIBRADCount++;
      while(digitalRead(LIBRADPin)==0){
      }
      attachInterrupt(0,countPulseLIBRADMints,FALLING);
}

void readLIBRADMints(uint8_t sampleTimeSeconds)  {

    LIBRADCount = 0;

    unsigned long sampleTimeMS = sampleTimeSeconds*1000;
    unsigned long startTime = millis();
    attachInterrupt(0,countPulseLIBRADMints,FALLING);
    while ((millis()-startTime) < sampleTimeMS) {
    }
    detachInterrupt(0);
    unsigned long timeSpent = millis()-startTime;

    float countPerMinute = (float(LIBRADCount)*float(60000))/float(timeSpent) ;
    float radiationValue = countPerMinute*CONV_FACTOR;
    String readings[3] = { String(countPerMinute,4), String(radiationValue,4), String(timeSpent)};
    sensorPrintNanoMints("LIBRAD",readings,3);

}

//
