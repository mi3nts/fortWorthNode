
#include "devicesMints.h"



void initializeSerialMints(){

  Serial.begin(9600);
  Serial.println("Serial Port Open");

}


void initializeHTU21DMints(){

  if (htu.begin()) {
    Serial.println("HTU21D Initiated");
    while (1);
  }else{
    Serial.println("HTU21D not found");
  }

}



void readHTU21DMints(){

  float temp = htu.readTemperature();
  float rel_hum = htu.readHumidity();
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C");
  Serial.print("\t\t");
  Serial.print("Humidity: "); Serial.print(rel_hum); Serial.println(" \%");
  delay(500);

}
