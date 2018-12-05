#include "jobsMints.h"

// Native Command
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:

    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '-') {
       stringComplete = true;
    }
  }
}


void initializeSerialMints(){

  Serial.begin(9600);
  Serial.println("Serial Port Open");

}

void commandReadMints(){
// Serial.println("inside");
  if (stringComplete) {
    Serial.println(inputString);
    sendCommand2DevicesMints(inputString);

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}


// String int2StringMints(int inputNumber){
//
// return String::format("%04d:%02d:%02d:%02d:%02d:%02d",inputNumber);
//
//   }
