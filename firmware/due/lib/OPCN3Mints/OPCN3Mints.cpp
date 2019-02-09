/***************************************************************************
  OPCN3Mints
  ---------------------------------
  Written by: Lakitha Omal Harindha Wijeratne
  - for -
  Mints: Multi-scale Integrated Sensing and Simulation
  ---------------------------------
  Date: November 29th, 2018
  ---------------------------------
  This library is written for the Alphasense OPCN3 optical particle counter.
  ----------------> http://www.alphasense.com/WEB1213/wp-content/uploads/2018/02/OPC-N3.pdf
  --------------------------------------------------------------------------
  https://github.com/mi3nts
  http://utdmints.info/

 ***************************************************************************/

#include "OPCN3Mints.h"
#include <Arduino.h>
#include <SPI.h>
/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/

 OPCN3Mints::OPCN3Mints(uint8_t chipSelect){
  alphaSlavePin  = chipSelect;
 }

// Alpha Sensor Functions
 void OPCN3Mints::begin()
{
    printMintsBegin();
    SerialUSB.println("Initiating SPI ");
    SPI.begin(alphaSlavePin);
    SPI.setBitOrder(MSBFIRST);
    delay(1000);
    pinMode(alphaSlavePin,OUTPUT);
    digitalWrite(alphaSlavePin,HIGH);
    SPI.setDataMode(alphaSlavePin, 0);
    SPI.setClockDivider(alphaSlavePin,168);
    delay(400);
    SerialUSB.println("---------------------------- ");
    printMintsEnd();

}


bool OPCN3Mints::initialize(){

        delay(1000);
        begin();
        delay(1000);
        readDACandPowerStatus();
        delay(1000);
        readInformationString();
        delay(1000);
        readSerialNumber();
        delay(1000);
        readFirmwareVersion();
        delay(1000);
        readConfigurationVariables();
        delay(10000);
        struct fanDigitalPotShutdownState fanState = setFanDigitalPotShutdownState(true);
        delay(1000);
        struct laserDigitalPotShutdownState laserState = setLaserDigitalPotShutdownState(true);
        delay(1000);
        struct highLowGainState gainState =  setHighLowGainState(true);
        delay(1000);
        bool reset = resetHistogram() ;
        return (fanState.valid&&reset)&&(laserState.valid&&gainState.valid);

  }







  struct fanDigitalPotShutdownState OPCN3Mints::setFanDigitalPotShutdownState(bool status) {

        printMintsBegin();
        SerialUSB.println("Setting Fan Digital Pot Shutdown State");
        int  size = 1;
        byte validator[2] = {0X31,0XF3};
        byte dataIn[size];
        byte initial[2];
        byte inputByte  =  0X03;;

        if(status){
            SerialUSB.println("Turning Fan On");
            beginTransfer();
            initial[0] = SPI.transfer(alphaSlavePin,inputByte);
            delay(10);
            initial[1] = SPI.transfer(alphaSlavePin,inputByte);
            delayMicroseconds(10);
            dataIn[0] = SPI.transfer(alphaSlavePin,0X03);
            endTransfer();
        }else{

          SerialUSB.println("Turning Fan Off");
          beginTransfer();
          initial[0] = SPI.transfer(alphaSlavePin,inputByte);
          delay(10);
          initial[1] = SPI.transfer(alphaSlavePin,inputByte);
          delayMicroseconds(10);
          dataIn[0] = SPI.transfer(alphaSlavePin,0X02);
          endTransfer();
        }



       printBytesRead(initial,dataIn,size);


       fanDigitalPotShutdownState dataOutput;
       dataOutput.valid        = comparator(validator, initial,2);
       dataOutput.fanOn        = status;




     SerialUSB.print("Validity: ");
     SerialUSB.println(dataOutput.valid);
     SerialUSB.print(dataOutput.fanOn);    SerialUSB.print(" ");
     printMintsEnd();

       return dataOutput;
    }


    struct laserDigitalPotShutdownState OPCN3Mints::setLaserDigitalPotShutdownState(bool status) {

          printMintsBegin();
          SerialUSB.println("Setting Laser Digital Pot Shutdown State");
          int  size = 1;
          byte validator[2] = {0X31,0XF3};
          byte dataIn[size];
          byte initial[2];
          byte inputByte  =  0X03;;

          if(status){
             SerialUSB.println("Turning Laser On");
             beginTransfer();
             initial[0] = SPI.transfer(alphaSlavePin,inputByte);
             delay(10);
             initial[1] = SPI.transfer(alphaSlavePin,inputByte);
             delayMicroseconds(10);
             dataIn[0] = SPI.transfer(alphaSlavePin,0X05);
             endTransfer();
          }else{
            SerialUSB.println("Turning Laser Off");
            beginTransfer();
            initial[0] = SPI.transfer(alphaSlavePin,inputByte);
            delay(10);
            initial[1] = SPI.transfer(alphaSlavePin,inputByte);
            delayMicroseconds(10);
            dataIn[0] = SPI.transfer(alphaSlavePin,0X04);
            endTransfer();
          }

         printBytesRead(initial,dataIn,size);


         laserDigitalPotShutdownState dataOutput;
         dataOutput.valid          = comparator(validator, initial,2);
         dataOutput.laserOn        = status;

       SerialUSB.print("Validity: ");
       SerialUSB.println(dataOutput.valid);
       SerialUSB.print(dataOutput.laserOn);    SerialUSB.print(" ");
       printMintsEnd();

         return dataOutput;
      }



      struct highLowGainState OPCN3Mints::setHighLowGainState(bool status) {

            printMintsBegin();
            SerialUSB.println("Setting Gain State");
            int  size = 1;
            byte validator[2] = {0X31,0XF3};
            byte dataIn[size];
            byte initial[2];
            byte inputByte  =  0X03;;

            if(status){
               SerialUSB.println("Setting a High Gain");
               beginTransfer();
               initial[0] = SPI.transfer(alphaSlavePin,inputByte);
               delay(10);
               initial[1] = SPI.transfer(alphaSlavePin,inputByte);
               delayMicroseconds(10);
               dataIn[0] = SPI.transfer(alphaSlavePin,0X07);
               endTransfer();
            }else{
              SerialUSB.println("Setting a Low Gain");
              beginTransfer();
              initial[0] = SPI.transfer(alphaSlavePin,inputByte);
              delay(10);
              initial[1] = SPI.transfer(alphaSlavePin,inputByte);
              delayMicroseconds(10);
              dataIn[0] = SPI.transfer(alphaSlavePin,0X06);
              endTransfer();
            }

           printBytesRead(initial,dataIn,size);


           highLowGainState dataOutput;
           dataOutput.valid          = comparator(validator, initial,2);
           dataOutput.highLow           = status;

         SerialUSB.print("Validity: ");
         SerialUSB.println(dataOutput.valid);
         SerialUSB.print(dataOutput.highLow);    SerialUSB.print(" ");
         printMintsEnd();

        return  dataOutput;
        }


struct DACandPowerStatus OPCN3Mints::readDACandPowerStatus() {
printMintsBegin();
      SerialUSB.println("Reading DAC and Power Status");
      int  size = 6;
      byte inputByte =  0X13;
      byte validator[2] = {0X31,0XF3};
      byte dataIn[size];
      byte initial[2];


      beginTransfer();
      initial[0] = SPI.transfer(alphaSlavePin,inputByte);
      delay(10);
      initial[1] = SPI.transfer(alphaSlavePin,inputByte);
      for (int i = 0 ; i<size; i++)
          {
          delayMicroseconds(10);
          dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
          }

     endTransfer();
     printBytesRead(initial,dataIn,size);


   DACandPowerStatus dataOutput;
   memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
   dataOutput.valid  = comparator(validator, initial,2);

   SerialUSB.print("Validity: ");
   SerialUSB.println(dataOutput.valid);
   SerialUSB.print(dataOutput.fanOn);    SerialUSB.print(" ");
   SerialUSB.print(dataOutput.laserDACOn);  SerialUSB.print(" ");
   SerialUSB.print(dataOutput.fanDACVal );  SerialUSB.print(" ");
   SerialUSB.print(dataOutput.laserDACVal);  SerialUSB.print(" ");
   SerialUSB.print(dataOutput.laserSwitch );  SerialUSB.print(" ");
   SerialUSB.print(dataOutput.gainAndAutoGainToggleSetting);  SerialUSB.print(" ");
   printMintsEnd();

     return dataOutput;
  }


struct informationString OPCN3Mints::readInformationString() {
printMintsBegin();
        SerialUSB.println("Reading Information String");
        int  size = 60;
        byte inputByte =  0X3F;
        byte validator[2] = {0X31,0XF3};
        byte dataIn[size];
        byte initial[2];
        String info = "";
        beginTransfer();
        initial[0] = SPI.transfer(alphaSlavePin,inputByte);
        delay(10);
        initial[1] = SPI.transfer(alphaSlavePin,inputByte);
        for (int i = 0 ; i<size; i++)
            {
            delayMicroseconds(10);
            dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
            }

       endTransfer();
       printBytesRead(initial,dataIn,size);

       for (int i = 0; i < 60; i++){
         info += String((char)dataIn[i]);
      }

     informationString dataOutput;
     dataOutput.valid        = comparator(validator, initial,2);
     dataOutput.information  = info;

     SerialUSB.print("Validity: ");
     SerialUSB.print(dataOutput.valid)      ;   SerialUSB.println(" ");
     SerialUSB.print(dataOutput.information);   SerialUSB.print(" ");
     printMintsEnd();

    return dataOutput;
    }


struct serialNumber OPCN3Mints::readSerialNumber() {
printMintsBegin();
            SerialUSB.println("Reading Serial Number");
            int  size = 60;
            byte inputByte =  0X10;
            byte validator[2] = {0X31,0XF3};
            byte dataIn[size];
            byte initial[2];
            String info = "";
            beginTransfer();
            initial[0] = SPI.transfer(alphaSlavePin,inputByte);
            delay(10);
            initial[1] = SPI.transfer(alphaSlavePin,inputByte);
            for (int i = 0 ; i<size; i++)
                {
                delayMicroseconds(10);
                dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
                }

           endTransfer();
           printBytesRead(initial,dataIn,size);

           for (int i = 0; i < size; i++){
             info += String((char)dataIn[i]);
          }

           serialNumber dataOutput;
           dataOutput.valid   = comparator(validator, initial,2);
           dataOutput.serial  = info;
          //

         SerialUSB.print("Validity: ");
         SerialUSB.print(dataOutput.valid) ;  SerialUSB.println(" ");
         SerialUSB.print(dataOutput.serial);  SerialUSB.print(" ");
         printMintsEnd();

return dataOutput;

}




struct firmwareVersion OPCN3Mints::readFirmwareVersion() {
printMintsBegin();
            SerialUSB.println("Reading Firmaware Version");
            int  size = 2;
            byte inputByte =  0X12;
            byte validator[2] = {0X31,0XF3};
            byte dataIn[size];
            byte initial[2];
            String info = "";
            beginTransfer();
            initial[0] = SPI.transfer(alphaSlavePin,inputByte);
            delay(10);
            initial[1] = SPI.transfer(alphaSlavePin,inputByte);
            for (int i = 0 ; i<size; i++)
                {
                delayMicroseconds(10);
                dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
                }

           endTransfer();
           printBytesRead(initial,dataIn,size);


           firmwareVersion dataOutput;

            memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
            dataOutput.valid  = comparator(validator, initial,2);

         SerialUSB.print("Validity: ");
         SerialUSB.print(dataOutput.valid)  ; SerialUSB.println(" ");
         SerialUSB.print(dataOutput.major);   SerialUSB.print(" ");
         SerialUSB.print(dataOutput.minor);   SerialUSB.print(" ");
         printMintsEnd();

return  dataOutput;

}



struct configurationVariables OPCN3Mints::readConfigurationVariables() {
printMintsBegin();
  SerialUSB.println("Reading Configuration Variables");
  int  size = 163;
  byte inputByte =  0X3C;
  byte validator[2] = {0X31,0XF3};
  byte dataIn[size];
  byte initial[2];
  String info = "";
  beginTransfer();
  initial[0] = SPI.transfer(alphaSlavePin,inputByte);
  delay(10);
  initial[1] = SPI.transfer(alphaSlavePin,inputByte);
  for (int i = 0 ; i<size; i++)
    {
        delayMicroseconds(10);
        dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
    }

  endTransfer();
  printBytesRead(initial,dataIn,size);

 configurationVariables dataOutput;

 memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
 dataOutput.valid  = comparator(validator, initial,2);

 SerialUSB.print("Validity: ");
 SerialUSB.println(dataOutput.valid);
 SerialUSB.println("Bin Boundries ADC");
 SerialUSB.print(dataOutput.binBoundriesADC0);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC1);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC2);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC3);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC4);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC5);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC6);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC7);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC8);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC9);SerialUSB.println(" ");
 SerialUSB.print(dataOutput.binBoundriesADC10);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC11);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC12);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC13);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC14);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC15);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC16);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC17);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC18);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC19);SerialUSB.println(" ");
 SerialUSB.print(dataOutput.binBoundriesADC20);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC21);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC22);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC23);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binBoundriesADC24);SerialUSB.println(" ");

SerialUSB.println("-------------------------------------------------");
SerialUSB.println("Bin Boundries Diametors");
       SerialUSB.print(dataOutput.binBoundriesDiametor0);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor1);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor2);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor3);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor4);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor5);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor6);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor7);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor8);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor9);SerialUSB.println(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor10);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor11);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor12);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor13);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor14);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor15);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor16);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor17);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor18);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor19);SerialUSB.println(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor20);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor21);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor22);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor23);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binBoundriesDiametor24);SerialUSB.println(" ");

SerialUSB.println("-------------------------------------------------");
SerialUSB.println("Bin Weights");
       SerialUSB.print(dataOutput.binWeightings0);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings1);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings2);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings3);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings4);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings5);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings6);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings7);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings8);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings9);SerialUSB.println(" ");
       SerialUSB.print(dataOutput.binWeightings10);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings11);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings12);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings13);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings14);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings15);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings16);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings17);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings18);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings19);SerialUSB.println(" ");
       SerialUSB.print(dataOutput.binWeightings20);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings21);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings22);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.binWeightings23);SerialUSB.println(" ");
SerialUSB.println("-------------------------------------------------");
SerialUSB.println("PM Diametors");
       SerialUSB.print(dataOutput.pmDiametorA);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.pmDiametorB);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.pmDiametorC);SerialUSB.println(" ");
SerialUSB.println("-------------------------------------------------");
SerialUSB.println("PM MSLNS");
       SerialUSB.print(dataOutput.maximumTimeOfFlight);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.AMSamplingIntervalCount);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.AMIdleIntervalCount);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.AMMaxDataArraysInFile);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.AMOnlySavePMData);SerialUSB.print(" ");
       SerialUSB.print(dataOutput.AMFanOnInIdle);SerialUSB.print(" ");

printMintsEnd();

return  dataOutput;

}


struct histogramData OPCN3Mints::readHistogramData() {
  printMintsBegin();
  SerialUSB.println("Reading Histogram Data ");
  int  size = 86;
  byte inputByte =  0X30;
  byte validator[2] = {0X31,0XF3};
  byte dataIn[size];
  byte initial[2];
  String info = "";
  beginTransfer();
  initial[0] = SPI.transfer(alphaSlavePin,inputByte);
  delay(10);
  initial[1] = SPI.transfer(alphaSlavePin,inputByte);
  for (int i = 0 ; i<size; i++)
    {
        delayMicroseconds(10);
        dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
    }

  endTransfer();
  printBytesRead(initial,dataIn,size);

 histogramData dataOutput;

 memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
 dataOutput.valid  = comparator(validator, initial,2);

 SerialUSB.print("Validity: ");
 SerialUSB.println(dataOutput.valid);
 SerialUSB.println("Bin Counts");
 SerialUSB.print(dataOutput.binCount0);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount1);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount2);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount3);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount4);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount5);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount6);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount7);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount8);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount9);SerialUSB.println(" ");
 SerialUSB.print(dataOutput.binCount10);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount11);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount12);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount13);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount14);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount15);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount16);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount17);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount18);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount19);SerialUSB.println(" ");
 SerialUSB.print(dataOutput.binCount20);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount21);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount22);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.binCount23);SerialUSB.println(" ");

 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("Time To Cross");
 SerialUSB.print(dataOutput.bin1TimeToCross);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.bin3TimeToCross);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.bin5TimeToCross);SerialUSB.print(" ");
 SerialUSB.print(dataOutput.bin7TimeToCross);SerialUSB.println(" ");

 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("Sampling Period");
 SerialUSB.println(dataOutput.samplingPeriod);
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("Sample Flow Rate");
 SerialUSB.println(dataOutput.sampleFlowRate);
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("Temperature");
 SerialUSB.println(dataOutput.temperature );
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("Humidity");
 SerialUSB.println(dataOutput.humidity );
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("pm1");
 SerialUSB.println(dataOutput.pm1);
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("pm2.5");
 SerialUSB.println(dataOutput.pm2_5);
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("pm10");
 SerialUSB.println(dataOutput.pm10);
 SerialUSB.println("-------------------------------------------------");

 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("MSLNS");

  SerialUSB.print(dataOutput.rejectCountGlitch);SerialUSB.print(" ");
  SerialUSB.print(dataOutput.rejectCountLongTOF);SerialUSB.print(" ");
  SerialUSB.print(dataOutput.rejectCountRatio);SerialUSB.print(" ");
  SerialUSB.print(dataOutput.rejectCountOutOfRange);SerialUSB.print(" ");
  SerialUSB.print(dataOutput.fanRevCount);SerialUSB.print(" ");
  SerialUSB.print(dataOutput.laserStatus);SerialUSB.print(" ");
  SerialUSB.print(dataOutput.checkSum);SerialUSB.print(" ");

printMintsEnd();

return  dataOutput;

}


struct pmData OPCN3Mints::readPMData() {
  printMintsBegin();
  SerialUSB.println("Reading Histogram Data ");
  int  size = 14;
  byte inputByte =  0X32;
  byte validator[2] = {0X31,0XF3};
  byte dataIn[size];
  byte initial[2];
  String info = "";
  beginTransfer();
  initial[0] = SPI.transfer(alphaSlavePin,inputByte);
  delay(10);
  initial[1] = SPI.transfer(alphaSlavePin,inputByte);
  for (int i = 0 ; i<size; i++)
    {
        delayMicroseconds(10);
        dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
    }

 endTransfer();
 printBytesRead(initial,dataIn,size);
 pmData dataOutput;

  memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
  dataOutput.valid  = comparator(validator, initial,2);

 SerialUSB.print("Validity: ");
 SerialUSB.println(dataOutput.valid);
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("pm1");
 SerialUSB.println(dataOutput.pm1);
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("pm2.5");
 SerialUSB.println(dataOutput.pm2_5);
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("pm10");
 SerialUSB.println(dataOutput.pm10);
 SerialUSB.println("-------------------------------------------------");
 SerialUSB.println("CheckSum");
 SerialUSB.print(dataOutput.checkSum);SerialUSB.print(" ");

printMintsEnd();

return  dataOutput;

}

bool OPCN3Mints::resetHistogram() {

  printMintsBegin();
  SerialUSB.println("Resetting Histogram");
  int  size = 14;
  byte inputByte =  0X32;
  byte validator[2] = {0X31,0XF3};
  byte dataIn[size];
  byte initial[2];
  beginTransfer();
  initial[0] = SPI.transfer(alphaSlavePin,inputByte);
  delay(10);
  initial[1] = SPI.transfer(alphaSlavePin,inputByte);
  for (int i = 0 ; i<size; i++)
    {
        delayMicroseconds(10);
        dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
    }

 endTransfer();
 printBytesRead(initial,dataIn,size);
 printMintsEnd();

return  comparator(validator, initial,2);

}

bool OPCN3Mints::comparator(byte arrayOne[], byte arrayTwo[], int size)
  {

    bool valid = true;

    for (int i = 0; i < size; i++){
         if (arrayOne[i] != arrayTwo[i])
           {
            valid = false;
           }
    }

    return valid;
  }



void OPCN3Mints::beginTransfer() {

   digitalWrite(alphaSlavePin, LOW);
  delay(1);
   }

void OPCN3Mints::endTransfer() {
delay(1);
   digitalWrite(alphaSlavePin, HIGH);

}


void OPCN3Mints::printBytesRead(byte initial[], byte dataIn[], int sizeOfArray)
{
    SerialUSB.println("--------------------------------");
    SerialUSB.println("Printing Initial Bytes----------");
    SerialUSB.print(initial[0],HEX);
    SerialUSB.print(" ");
    SerialUSB.print(initial[1],HEX);
    SerialUSB.println("");
    SerialUSB.println("--------------------------------");
    SerialUSB.println("Printing Byte Array-------------");

    for (int i = 0 ; i<sizeOfArray; i++)
        {
            SerialUSB.print(dataIn[i],HEX);
            SerialUSB.print(" ");
            if(i%10==9)
              {
              SerialUSB.println("");
              }
        }

  SerialUSB.println("");
  SerialUSB.println("--------------------------------");
}



void OPCN3Mints::printMintsBegin(){
  SerialUSB.println("");
  SerialUSB.println("--------------------------------");
  SerialUSB.println("-------------MINTS--------------");

}


  void OPCN3Mints::printMintsEnd(){
    SerialUSB.println("");
    SerialUSB.println("-------------MINTS--------------");
    SerialUSB.println("--------------------------------");
}
