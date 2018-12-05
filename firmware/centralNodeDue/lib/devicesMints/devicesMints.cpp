
#include "devicesMints.h"

void sendCommand2DevicesMints(String command){

      if (command.startsWith("mints:")) {
        printInput("Recieving Mints Command");

      if (command.startsWith("HTU21D",6)) {
        readHTU21DMints();
      }

      if (command.startsWith("BMP280",6)) {
        readBMP280Mints();
        // SerialUSB.println(year());
      }

      if (command.startsWith("time",6)) {
        setTimeMints(command.substring(11));

        }

    }
}


//
void  setTimeMints(String command){
      printInput(command);
      int year   = command.substring(0, 4).toInt();
      int month  = command.substring(4,6).toInt();
      int day    = command.substring(6,8).toInt();
      int hour   = command.substring(8,10).toInt();
      int minute = command.substring(10,12).toInt();
      int second = command.substring(12,14).toInt();
      setTime(second,minute,hour,day,month,year);

  }


void printInput(String command){
      SerialUSB.print("-");
      SerialUSB.print(command);
      SerialUSB.print("-");
}


//
// String getTimeMints(){
//   return String::format("%04d:%02d:%02d:%02d:%02d:%02d",year(),month(),day(),hour(),minute(),second());
// }




// HTU21D ---------------------------------------
void initializeHTU21DMints(){

  if (htu.begin()) {
    Serial.println("HTU21D Initiated");
    delay(1);
  }else{
    Serial.println("HTU21D not found");
  }

}

void readHTU21DMints(){

  float temperature = htu.readTemperature();
  float humidity    = htu.readHumidity();
  SerialUSB.print("- HTU21D;");printTimeOnlyMints();SerialUSB.print(";");SerialUSB.print(temperature);SerialUSB.print(":");SerialUSB.print(humidity);SerialUSB.print("-");
}


void printTimeMints(){
    SerialUSB.print("-") ;
    SerialUSB.print(year()) ;
    SerialUSB.print(":") ;
    SerialUSB.print(month()) ;
    SerialUSB.print(":") ;
    SerialUSB.print(day());
    SerialUSB.print(":") ;
    SerialUSB.print((hour())) ;
    SerialUSB.print(":") ;
    SerialUSB.print(minute()) ;
    SerialUSB.print(":") ;
    SerialUSB.print(second()) ;
    SerialUSB.print("-") ;
}


void printTimeOnlyMints(){
    SerialUSB.print(year()) ;
    SerialUSB.print(":") ;
    SerialUSB.print(month()) ;
    SerialUSB.print(":") ;
    SerialUSB.print(day());
    SerialUSB.print(":") ;
    SerialUSB.print((hour())) ;
    SerialUSB.print(":") ;
    SerialUSB.print(minute()) ;
    SerialUSB.print(":") ;
    SerialUSB.print(second()) ;

}












// BMP280  ---------------------------------------

void initializeBMP280Mints(){

  if (bme.begin()) {
    Serial.println("BMP280 Initiated");
    delay(1);
  }else{
    Serial.println("BMP280 not found");
  }

}

void readBMP280Mints(){

  float temperature    = bme.readTemperature();
  float pressure       = bme.readPressure();
  SerialUSB.print("-BMP280;"); printTimeOnlyMints();SerialUSB.print(";");SerialUSB.print(temperature);SerialUSB.print(":");SerialUSB.print(pressure);SerialUSB.print("-");

}
