# 1 "/tmp/tmpRyyja7"
#include <Arduino.h>
# 1 "/media/teamlary/Team_Lary_1/gitGubRepos/Lakitha/centralNode/firmware/centralNodeDue/src/main.ino"
#include <Arduino.h>
#include <devicesMints.h>
#include <jobsMints.h>
#include <Wire.h>
#include <Adafruit_HTU21DF.h>


Adafruit_HTU21DF htu = Adafruit_HTU21DF();
Adafruit_BMP280 bme;


String inputString = "";
bool stringComplete = false;
void setup();
void loop();
#line 17 "/media/teamlary/Team_Lary_1/gitGubRepos/Lakitha/centralNode/firmware/centralNodeDue/src/main.ino"
void setup() {

   initializeSerialMints();
   initializeHTU21DMints();
   initializeBMP280Mints();
   inputString.reserve(200);
   SerialUSB.begin(9600);
}



void loop() {
  commandReadMints();
# 46 "/media/teamlary/Team_Lary_1/gitGubRepos/Lakitha/centralNode/firmware/centralNodeDue/src/main.ino"
}