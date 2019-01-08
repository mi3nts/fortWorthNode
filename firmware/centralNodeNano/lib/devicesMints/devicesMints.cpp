
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
    unsigned long lowpulseoccupancy = 0;
    float ratio = 0;
    float concentration = 0;

    starttime = millis();

    while ((millis()-starttime) < sampletime_ms) {
        duration = pulseIn(PPD42NSPin, LOW);
        lowpulseoccupancy = lowpulseoccupancy + duration;
    }

    unsigned long timeSpent = millis()-starttime;
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    String readings[4] = { String(lowpulseoccupancy), String(concentration,4), String(ratio,4), String(timeSpent) };
    sensorPrintNanoMints("PPD42NS",readings,4);

}


// // LIBRad ---------------------------------------

bool initializeLIBRadMints(){
    pinMode(LIBRadPin, INPUT);
    digitalWrite(LIBRadPin,HIGH);
    delay(1);
    return true;
  }

void countPulseLIBRadMints(){

      detachInterrupt(0);
      LIBRadCount++;
      while(digitalRead(LIBRadPin)==0){
      }
      attachInterrupt(0,countPulseLIBRadMints,FALLING);
}

void readLIBRadMints(uint8_t sampleTimeSeconds)  {

    LIBRadCount = 0;

    unsigned long sampleTimeMS = sampleTimeSeconds*1000;
    unsigned long startTime = millis();
    attachInterrupt(0,countPulseLIBRadMints,FALLING);
    while ((millis()-startTime) < sampleTimeMS) {
    }
    detachInterrupt(0);
    unsigned long timeSpent = millis()-startTime;

    float countPerMinute = (float(LIBRadCount)*float(60000))/float(timeSpent) ;
    float radiationValue = countPerMinute*CONV_FACTOR;
    String readings[2] = { String(countPerMinute,4), String(radiationValue,4)};
    sensorPrintNanoMints("LIBRad",readings,2);

}

//
