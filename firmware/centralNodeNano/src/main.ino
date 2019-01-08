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

  // if(PPD42NSOnline)
  //     {
  //       readPPD42NSMints(5);
  //     }

  if(LIBRadOnline)
      {
        readLIBRadMints(5);
      }

}










// Conversion factor - CPM to uSV/h
// #define CONV_FACTOR 0.00812

// int geiger_input = 3;
// long count = 0;
// long countPerMinute = 0;
// long timePrevious = 0;
// long timePreviousMeassure = 0;
// long time = 0;
// long countPrevious = 0;
// float radiationValue = 0.0;


// void countPulse(){
//   detachInterrupt(0);
//   count++;
//   while(digitalRead(geiger_input)==0){
//   }
//   attachInterrupt(0,countPulse,FALLING);
// }
//
//
// void setup(){
//   pinMode(geiger_input, INPUT);
//   digitalWrite(geiger_input,HIGH);
//
//   Serial.begin(19200);
//
//   //set up the LCD\'s number of columns and rows:
//   delay(1000);

//   attachInterrupt(0,countPulse,FALLING);
//
// }
//
// void loop(){
//
//   if (millis()-timePreviousMeassure > 10000){
//     Serial.println("-----------------Mints-------------------");
//     Serial.println("-----------------------------------------");
//     countPerMinute = 6*count;
//     radiationValue = countPerMinute * CONV_FACTOR;
//     timePreviousMeassure = millis();
//     Serial.print("cpm = ");
//     Serial.print(countPerMinute,DEC);
//     Serial.print(" - ");
//     Serial.print("uSv/h = ");
//     Serial.println(radiationValue,4);
//     count = 0;
//
//     Serial.println("-----------------------------------------");
//     Serial.println("-----------------Mints-------------------");
//
//   }
//
// }











//     if(HTU21DOnline)
//     {
//       readHTU21DMints();
//     }
//
// delay(2000);
//
//     if(BMP280Online)
//     {
//       readBMP280Mints();
//     }
//
// delay(2000);
//
//    if(OPCN3Online)
//       {
//          readOPCN3Mints();
//       }
// delay(2000);



      // delay(5000);
      // OPCN3.readPMData();
      //
   //   // // }
   //  float  lk = 12.2392;
   //  String lks = String(lk,4);
   //  Serial.println(lks);
   //  // String lkt = {"sskjfsf","fjfsadffg"};
   //  // sensorPrintMints("HTU21D",lkt,2);
   //
   // String ordinal[5] = { "first", "second", "third", "fourth", "fifth"};
   //
   //
   //  sensorPrintMints("String sensor",ordinal,5);



//
