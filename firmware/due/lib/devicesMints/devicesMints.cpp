
#include "devicesMints.h"


// HTU21D ---------------------------------------
bool initializeHTU21DMints(){
  if (htu.begin()) {
    Serial.println("HTU21D Initiated");
    delay(1);
    return true;
  }else{
    Serial.println("HTU21D not found");
    delay(1);
    return false;
  }

}

void readHTU21DMints(){

  float temperature = htu.readTemperature();
  float humidity    = htu.readHumidity();

  String readings[2] = { String(temperature,2) , String(humidity,2) };
  sensorPrintMints("HTU21D",readings,2);

}

// // BMP280  ---------------------------------------

bool initializeBMP280Mints(){

  if (bmp.begin()) {
    Serial.println("BMP280 Initiated");
    delay(1);
  return true;
    /* Default settings from datasheet. */




  }else{
    Serial.println("BMP280 not found");
    delay(1);
    return false;
  }

}

void readBMP280Mints(){

  float temperature    = bmp.readTemperature();
  float pressure       = bmp.readPressure();

  String readings[2] = { String(temperature,2) , String(pressure,2) };
  sensorPrintMints("BMP280",readings,2);
}



// // BME280  ---------------------------------------

bool initializeBME280Mints(){


      if (bme280.init()) {
        Serial.println("BME280 Initiated");
        delay(1);
        return true;
      }
      else
      {
      Serial.println("BME280 not found");
      delay(1);
      return false;
      }
}

void readBME280Mints(){



  float temperature    = bme280.getTemperature();
  float pressure       = bme280.getPressure();
  float humidity       = bme280.getHumidity();
  float altitude       = bme280.calcAltitude(pressure);

  String readings[4] = { String(temperature,2) , String(pressure,2), String(humidity,2) , String(altitude,2) };
  sensorPrintMints("BME280",readings,4);
}









// INA219  ---------------------------------------

bool initializeINA219Mints(){
    ina.begin();
    Serial.println("INA219 Initiated");
    delay(1);
    return true;
}

void readINA219Mints(){

  float shuntVoltage  = ina.getShuntVoltage_mV();
  float busVoltage    = ina.getBusVoltage_V();
  float currentMA     = ina.getCurrent_mA();
  float powerMW      = ina.getPower_mW();
  float loadVoltage  = busVoltage + (shuntVoltage / 1000);


  String readings[5] = { String(shuntVoltage,4) , String(busVoltage,4),  String(currentMA,4) , String(powerMW,4), String(loadVoltage,4)};
  sensorPrintMints("INA219",readings,5);


}



// // OPCN3  ---------------------------------------

bool initializeOPCN3Mints(){

  return opc.initialize();

}

void readOPCN3Mints(){

  struct histogramData  allData= opc.readHistogramData();

  String readings[43] =  { \
                          String(allData.valid), \
                          String(allData.binCount0), \
                          String(allData.binCount1), \
                          String(allData.binCount2), \
                          String(allData.binCount3), \
                          String(allData.binCount4), \
                          String(allData.binCount5), \
                          String(allData.binCount6), \
                          String(allData.binCount7), \
                          String(allData.binCount8), \
                          String(allData.binCount9), \
                          String(allData.binCount10), \
                          String(allData.binCount11), \
                          String(allData.binCount12), \
                          String(allData.binCount13), \
                          String(allData.binCount14), \
                          String(allData.binCount15), \
                          String(allData.binCount16), \
                          String(allData.binCount17), \
                          String(allData.binCount18), \
                          String(allData.binCount19), \
                          String(allData.binCount20), \
                          String(allData.binCount21), \
                          String(allData.binCount22), \
                          String(allData.binCount23), \
                          String(allData.bin1TimeToCross), \
                          String(allData.bin3TimeToCross), \
                          String(allData.bin5TimeToCross), \
                          String(allData.bin7TimeToCross), \
                          String(allData.samplingPeriod), \
                          String(allData.sampleFlowRate), \
                          String(allData.temperature), \
                          String(allData.humidity), \
                          String(allData.pm1,2), \
                          String(allData.pm2_5,2), \
                          String(allData.pm10,2), \
                          String(allData.rejectCountGlitch), \
                          String(allData.rejectCountLongTOF), \
                          String(allData.rejectCountRatio), \
                          String(allData.rejectCountOutOfRange), \
                          String(allData.fanRevCount), \
                          String(allData.laserStatus), \
                          String(allData.checkSum) \
                        };

  sensorPrintMints("OPCN3",readings,43);



}






// //
// void  setTimeMints(String command){
//       printInput(command);
//       int year   = command.substring(0, 4).toInt();
//       int month  = command.substring(4,6).toInt();
//       int day    = command.substring(6,8).toInt();
//       int hour   = command.substring(8,10).toInt();
//       int minute = command.substring(10,12).toInt();
//       int second = command.substring(12,14).toInt();
//       setTime(second,minute,hour,day,month,year);
//
//   }
//
//
// void printInput(String command){
//       SerialUSB.print("-");
//       SerialUSB.print(command);
//       SerialUSB.print("-");
// }
//
//
// //
// // String getTimeMints(){
// //   return String::format("%04d:%02d:%02d:%02d:%02d:%02d",year(),month(),day(),hour(),minute(),second());
// // }
//
//
//
// void printTimeMints(){
//     SerialUSB.print("-") ;
//     SerialUSB.print(year()) ;
//     SerialUSB.print(":") ;
//     SerialUSB.print(month()) ;
//     SerialUSB.print(":") ;
//     SerialUSB.print(day());
//     SerialUSB.print(":") ;
//     SerialUSB.print((hour())) ;
//     SerialUSB.print(":") ;
//     SerialUSB.print(minute()) ;
//     SerialUSB.print(":") ;
//     SerialUSB.print(second()) ;
//     SerialUSB.print("-") ;
// }
//
//
// void printTimeOnlyMints(){
//     SerialUSB.print(year()) ;
//     SerialUSB.print(":") ;
//     SerialUSB.print(month()) ;
//     SerialUSB.print(":") ;
//     SerialUSB.print(day());
//     SerialUSB.print(":") ;
//     SerialUSB.print((hour())) ;
//     SerialUSB.print(":") ;
//     SerialUSB.print(minute()) ;
//     SerialUSB.print(":") ;
//     SerialUSB.print(second()) ;
//
// }
//
//
