
#include "jobsMints.h"
#include "devicesMints.h"


// Native Command
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


void initializeSerialMints(){

  Serial.begin(9600);
  Serial.println("Serial Port Open");

}

void commandReadMints(){

  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}
