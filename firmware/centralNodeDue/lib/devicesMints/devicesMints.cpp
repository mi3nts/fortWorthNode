
#include "devicesMints.h"

//
























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
  float humidity = htu.readHumidity();
  Serial.print("HTU21D Temprature: "); Serial.print(temperature); Serial.print(" C");
  Serial.print("\t\t");
  Serial.print("HTU21D Pressure  : "); Serial.print(humidity); Serial.println(" \%");

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

  Serial.print("BMP280 Temprature: "); Serial.print(temperature); Serial.print(" C");
  Serial.print("\t\t");
  Serial.print("BMP280 Pressure  : "); Serial.print(pressure); Serial.println(" Pa");

}
