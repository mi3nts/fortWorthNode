#include <Arduino.h>
#include <devicesMints.h>
#include <Wire.h>
#include <Adafruit_HTU21DF.h>


Adafruit_HTU21DF htu = Adafruit_HTU21DF();


void setup() {

  initializeSerialMints();
  initializeHTU21DMints();





}

// the loop routine runs over and over again forever:
void loop() {

  Serial.println("Hello Mints");
  readHTU21DMints();
  delay(1000);        // delay in between reads for stability
}
