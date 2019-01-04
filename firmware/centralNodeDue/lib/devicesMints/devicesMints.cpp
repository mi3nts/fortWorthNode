
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
  // SerialUSB.print("-HTU21D;");SerialUSB.print(";");SerialUSB.print(temperature);SerialUSB.print(":");SerialUSB.print(humidity);SerialUSB.print("-");

  //   if(serialOut){
  //       Serial.print("-HTU21D;");Serial.print(";");Serial.print(temperature);Serial.print(":");Serial.print(humidity);Serial.print("-");
  //   }

  // sensorPrintMints();




//
// // BMP280  ---------------------------------------

bool initializeBMP280Mints(){

  if (bme.begin()) {
    Serial.println("BMP280 Initiated");
    delay(1);
    return true;
  }else{
    Serial.println("BMP280 not found");
    delay(1);
    return false;
  }

}

void readBMP280Mints(){

  float temperature    = bme.readTemperature();
  float pressure       = bme.readPressure();

  String readings[2] = { String(temperature,2) , String(pressure,2) };
  sensorPrintMints("BMP280",readings,2);
}


// // INA219  ---------------------------------------
//
// void initializeINA219Mints(){
//
//   if (ina219.begin()) {
//     Serial.println("INA219 Initiated");
//     delay(1);
//   }else{
//     Serial.println("INA219 not found");
//   }
//
// }
//
// void readINA219Mints(){
//
//   float shuntvoltage = 0;
//   float busvoltage = 0;
//   float current_mA = 0;
//   float loadvoltage = 0;
//   float power_mW = 0;
//
//   shuntvoltage = ina219.getShuntVoltage_mV();
//   busvoltage   = ina219.getBusVoltage_V();
//   current_mA   = ina219.getCurrent_mA();
//   power_mW     = ina219.getPower_mW();
//   loadvoltage  = busvoltage + (shuntvoltage / 1000);
//
//   Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
//   Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
//   Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
//   Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
//   Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
//   Serial.println("");
//
//   SerialUSB.print("-BMP280;"); printTimeOnlyMints();SerialUSB.print(";");SerialUSB.print(temperature);SerialUSB.print(":");SerialUSB.print(pressure);SerialUSB.print("-");
//
// }







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
