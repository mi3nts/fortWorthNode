
#include "devicesMints.h"

// // PPD42NS ---------------------------------------
bool initializePPD42NSMints(){
    pinMode(PPD42NSPin,INPUT);
    delay(1);
    return true;
  }

void readPPD42NSMints(uint8_t sampleTimeSeconds)  {

    unsigned long duration;
    unsigned long starttime;
    unsigned long sampletime_ms = sampleTimeSeconds*1000;//sampe 30s ;
    unsigned long lowPulseOccupancy = 0;
    float ratio = 0;
    float concentration = 0;

    starttime = millis();

    while ((millis()-starttime) < sampletime_ms) {
        duration = pulseIn(PPD42NSPin, LOW);
        lowPulseOccupancy = lowPulseOccupancy + duration;
    }

    unsigned long timeSpent = millis()-starttime;
    ratio = lowPulseOccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    String readings[4] = { String(lowPulseOccupancy), String(concentration,4), String(ratio,4), String(timeSpent) };
    sensorPrintMints("PPD42NS",readings,4);

}


// // LIBRad ---------------------------------------

bool initializeLIBRADMints(){
    pinMode(LIBRADPin, INPUT);
    digitalWrite(LIBRADPin,HIGH);
    delay(1);
    return true;
  }

void countPulseLIBRADMints(){

      detachInterrupt(0);
      LIBRADCount++;
      while(digitalRead(LIBRADPin)==0){
      }
      attachInterrupt(0,countPulseLIBRADMints,FALLING);
}

void readLIBRADMints(uint8_t sampleTimeSeconds)  {

    LIBRADCount = 0;

    unsigned long sampleTimeMS = sampleTimeSeconds*1000;
    unsigned long startTime = millis();
    attachInterrupt(0,countPulseLIBRADMints,FALLING);
    while ((millis()-startTime) < sampleTimeMS) {
    }
    detachInterrupt(0);
    unsigned long timeSpent = millis()-startTime;

    float countPerMinute = (float(LIBRADCount)*float(60000))/float(timeSpent) ;
    float radiationValue = countPerMinute*CONV_FACTOR;
    String readings[4] = { String(countPerMinute,4), String(radiationValue,4), String(timeSpent),String(LIBRADCount)};
    sensorPrintMints("LIBRAD",readings,4);

}



// VEML6070 ---------------------------------------
bool initializeVEML6070Mints(){
    veml.begin(VEML6070_4_T);
    Serial.println("VEML6070 Initiated");
    delay(1);
    return true;

}

void readVEML6070Mints(){

  float UVLightLevel = veml.readUV();

  String readings[1] = { String(UVLightLevel,2) };
  sensorPrintMints("VEML6070",readings,1);

}


// TSL2591 ---------------------------------------
bool initializeTSL2591Mints()
{
  if (tsl.begin())
  {
    delay(10);
    displayTSL2591DetailsMints();
    delay(10);
    configureTSL2591Mints();
    Serial.println("TSL2591 Initiated");
    delay(1);
    return true;
  }else
  {
    Serial.println("TSL2591 not found");
    delay(1);
    return false;
  }
}

void readTSL2591Mints(){

  uint32_t luminosity      = tsl.getFullLuminosity();
  uint16_t ir              = luminosity >> 16;
  uint16_t full            = luminosity & 0xFFFF;
  uint16_t visible         = full - ir;
  float    lux             = tsl.calculateLux(full, ir);

  String readings[5] = { String(luminosity) ,  String(ir) , String(full) , String(visible) , String(lux,6) };
  sensorPrintMints("TSL2591",readings,5);

}


/**************************************************************************/
/*
    Taken from:
    https://github.com/adafruit/Adafruit_TSL2591_Library/blob/master/examples/tsl2591/tsl2591.ino
*/
/**************************************************************************/

void displayTSL2591DetailsMints(void)
{
    sensor_t sensor;
    tsl.getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:    ")); Serial.print(sensor.max_value); Serial.println(F(" lux"));
    Serial.print  (F("Min Value:    ")); Serial.print(sensor.min_value); Serial.println(F(" lux"));
    Serial.print  (F("Resolution:   ")); Serial.print(sensor.resolution, 4); Serial.println(F(" lux"));
    Serial.println(F("------------------------------------"));
    Serial.println(F(""));
    delay(500);
}

/**************************************************************************/
/*
    Configures the gain and integration time for the TSL2591
*/
/**************************************************************************/
void configureTSL2591Mints(void)
{


    // You can change the gain on the fly, to adapt to brighter/dimmer light situations
    //tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
    tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
    //tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain

    // Changing the integration time gives you a longer time over which to sense light
    // longer timelines are slower, but are good in very low light situtations!
    //tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
    // tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);
    tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
    // tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS);
    // tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
    // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);  // longest integration time (dim light)

    /* Display the gain and integration time for reference sake */
    Serial.println(F("------------------------------------"));
    Serial.print  (F("Gain:         "));
    tsl2591Gain_t gain = tsl.getGain();
    switch(gain)
    {
      case TSL2591_GAIN_LOW:
        Serial.println(F("1x (Low)"));
        break;
      case TSL2591_GAIN_MED:
        Serial.println(F("25x (Medium)"));
        break;
      case TSL2591_GAIN_HIGH:
        Serial.println(F("428x (High)"));
        break;
      case TSL2591_GAIN_MAX:
        Serial.println(F("9876x (Max)"));
        break;
    }
    Serial.print  (F("Timing:       "));
    Serial.print((tsl.getTiming() + 1) * 100, DEC);
    Serial.println(F(" ms"));
    Serial.println(F("------------------------------------"));
    Serial.println(F(""));
}



void advancedReadTSL2591Mnits(void)
{
    // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
    // That way you can do whatever math and comparisons you want!
    uint32_t lum = tsl.getFullLuminosity();
    uint16_t ir, full;
    ir = lum >> 16;
    full = lum & 0xFFFF;
    Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
    Serial.print(F("IR: ")); Serial.print(ir);  Serial.print(F("  "));
    Serial.print(F("Full: ")); Serial.print(full); Serial.print(F("  "));
    Serial.print(F("Visible: ")); Serial.print(full - ir); Serial.print(F("  "));
    Serial.print(F("Lux: ")); Serial.println(tsl.calculateLux(full, ir), 6);
}


/**************************************************************************/
/*
    Ends functions taken from:
    https://github.com/adafruit/Adafruit_TSL2591_Library/blob/master/examples/tsl2591/tsl2591.ino
*/
/**************************************************************************/

  /* Display some basic information on this sensor */
//////////////////////////////////////////
