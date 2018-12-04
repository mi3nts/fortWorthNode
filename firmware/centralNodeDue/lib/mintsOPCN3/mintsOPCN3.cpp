/***************************************************************************
  mintsOPCN3
  ---------------------------------
  Written by: Lakitha Omal Harindha Wijeratne
  - for -
  Mints: Multi-scale Integrated Sensing and Simulation
  ---------------------------------
  Date: November 29th, 2018
  ---------------------------------
  This library is written for the Alphasense OPCN3 optical particle counter.
  ----------------> http://www.alphasense.com/WEB1213/wp-content/uploads/2018/02/OPC-N3.pdf
  --------------------------------------------------------------------------
    https://github.com/mi3nts
    http://utdmints.info/

 ***************************************************************************/
#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include "mintsOPCN3.h"


/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/

 mintsOPCN3::mintsOPCN3(uint8_t chipSelect){
  alphaSlavePin  = chipSelect;
 }

// Alpha Sensor Functions

 void mintsOPCN3::begin()
{
    Serial.println("Initiating SPI ");
    SPI.begin(alphaSlavePin);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE1);
    SPI.setClockSpeed(300000);
	  pinMode(_cs, OUTPUT);
    Serial.println("Begining SPI");
}


 void mintsOPCN3::beginTransfer() {
    digitalWrite(alphaSlavePin, LOW);
    delay(1);
}

 void mintsOPCN3::endTransfer() {
    delay(1);
    digitalWrite(alphaSlavePin, HIGH);
}


bool mintsOPCN3::transferUntilMatch(byte send, byte wanted, unsigned long timeOut) {

    unsigned long startTime = millis();
    byte received;
    while (millis() - startTime < timeOut) {
        received = transfer(send);
        if (received == wanted)
        {
          return true;
        }
        else if(received == 0x31)
        {
        delay(12);
        }else
        {
        delay(2100);
        }
    }

    Serial.println("Match Failed, received Byte: "+ String(received,HEX));
    return false;
}


byte mintsOPCN3::transferByte(byte send) {
    return SPI.transfer(send);
}





void mintsOPCN3::initializeOPCN3{

    while (!setFanDigitalPotStateOPCN3(true)) {
        Serial.println("Still trying to turn on device...");
        delay(1000);
    }

    delay(1000);

    while (!setLaserPowerSwitchStateOPCN3(true)) {
        Serial.println("Still trying to turn on device...");
        delay(2500);
    }

        delay(1000);
    readPMOnlyOPCN3() ;

}



bool setFanDigitalPotStateOPCN3(bool powered) {
    Serial.println("Setting Fan Digital Pot State");

    beginTransfer();

    if (!transferUntilMatch(0x03, 0xf3, 5000)) {
        Serial.println("Power control timed out.");
        return false;
    }

    delayMicroseconds(10);

    if (powered) {
        transfer(0x03);
    } else {
        transfer(0x02);
    }

    endTransfer();

    return true;
}


bool Set_Laser_Digital_Pot_State_OPCN3(bool powered) {
    Serial.println("Setting Laser Digital Pot State");

    beginTransfer();

    if (!transferUntilMatch(0x03, 0xf3, 5000)) {
        Serial.println("Power control timed out.");
        return false;
    }

    delayMicroseconds(10);

    if (powered) {
        transfer(0x05);
    } else {
        transfer(0x02);
    }

    endTransfer();

    return true;
}



bool Set_Laser_Power_Switch_State_OPCN3(bool powered) {
    Serial.println("Setting Laser Power Switch State");

    beginTransfer();

    if (!transferUntilMatch(0x03, 0xf3, 5000)) {
        Serial.println("Power control timed out.");
        return false;
    }

    delayMicroseconds(10);

    if (powered) {
        transfer(0x07);
    } else {
        transfer(0x02);
    }

    endTransfer();

    return true;
}



bool Set_Gain_State_OPCN3(bool powered) {
    Serial.println("Setting Laser Gain State");

    beginTransfer();

    if (!transferUntilMatch(0x03, 0xf3, 5000)) {
        Serial.println("Power control timed out.");
        return false;
    }

    delayMicroseconds(10);

    if (powered) {
        transfer(0x09);
    } else {
        transfer(0x02);
    }

    endTransfer();

    return true;
}



bool Read_OPCN3_BW() {
    byte Alpha_Readings[86];

    beginTransfer();

    if (!transferUntilMatch(0x30, 0xf3, 5000)) {
        Serial.println("Histogram command failed.");
        return false;
    }

    delay(10);
    DateTime now = rtc.now();
    for (int i = 0; i<86; i++){
        Alpha_Readings[i] = transfer(0x30);
        delayMicroseconds(10);
    }

    endTransfer();

    Serial.println("Histogram:");

    for (int i = 0 ; i<86; i++) {
        Serial.print(Alpha_Readings[i], HEX);

        if (i % 10 == 9) {
            Serial.print("\n");
        } else {
            Serial.print(" ");
        }
    }

    Serial.println();

    Serial.println("--------");

    uint16_t OPCN3Bin0  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,0);
    uint16_t OPCN3Bin1  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,2);
    uint16_t OPCN3Bin2  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,4);
    uint16_t OPCN3Bin3  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,6);
    uint16_t OPCN3Bin4  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,8);
    uint16_t OPCN3Bin5  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,10);
    uint16_t OPCN3Bin6  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,12);
    uint16_t OPCN3Bin7  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,14);
    uint16_t OPCN3Bin8  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,16);
    uint16_t OPCN3Bin9  = Get_Int_From_Bytes_16_Bit(Alpha_Readings,18);
    uint16_t OPCN3Bin10 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,20);
    uint16_t OPCN3Bin11 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,22);
    uint16_t OPCN3Bin12 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,24);
    uint16_t OPCN3Bin13 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,26);
    uint16_t OPCN3Bin14 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,28);
    uint16_t OPCN3Bin15 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,30);
    uint16_t OPCN3Bin16 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,32);
    uint16_t OPCN3Bin17 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,34);
    uint16_t OPCN3Bin18 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,36);
    uint16_t OPCN3Bin19 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,38);
    uint16_t OPCN3Bin20 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,40);
    uint16_t OPCN3Bin21 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,42);
    uint16_t OPCN3Bin22 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,44);
    uint16_t OPCN3Bin23 = Get_Int_From_Bytes_16_Bit(Alpha_Readings,46);
    float   OPCN3PM1             = Get_Float_From_Bytes_32_Bit(Alpha_Readings,60);
    float   OPCN3PM2_5           = Get_Float_From_Bytes_32_Bit(Alpha_Readings,64);
    float   OPCN3PM10            = Get_Float_From_Bytes_32_Bit(Alpha_Readings,68);
    uint16_t OPCN3SamplingTime    = 20*Get_Int_From_Bytes_16_Bit(Alpha_Readings,52);
    uint16_t OPCN3Temperature     = Get_Int_From_Bytes_16_Bit(Alpha_Readings,56);
    uint16_t OPCN3Humidity        = 2*Get_Int_From_Bytes_16_Bit(Alpha_Readings,58);

    Serial.println("Bin 0  :"+String(OPCN3Bin0));
    Serial.println("Bin 1  :"+String(OPCN3Bin1));
    Serial.println("Bin 2  :"+String(OPCN3Bin2));
    Serial.println("Bin 3  :"+String(OPCN3Bin3));
    Serial.println("Bin 4  :"+String(OPCN3Bin4));
    Serial.println("Bin 5  :"+String(OPCN3Bin5));
    Serial.println("Bin 6  :"+String(OPCN3Bin6));
    Serial.println("Bin 7  :"+String(OPCN3Bin7));
    Serial.println("Bin 8  :"+String(OPCN3Bin8));
    Serial.println("Bin 9  :"+String(OPCN3Bin9));
    Serial.println("Bin 10 :"+String(OPCN3Bin10));
    Serial.println("Bin 11 :"+String(OPCN3Bin11));
    Serial.println("Bin 12 :"+String(OPCN3Bin12));
    Serial.println("Bin 13 :"+String(OPCN3Bin13));
    Serial.println("Bin 14 :"+String(OPCN3Bin14));
    Serial.println("Bin 15 :"+String(OPCN3Bin15));
    Serial.println("Bin 16 :"+String(OPCN3Bin16));
    Serial.println("Bin 17 :"+String(OPCN3Bin17));
    Serial.println("Bin 18 :"+String(OPCN3Bin18));
    Serial.println("Bin 19 :"+String(OPCN3Bin19));
    Serial.println("Bin 20 :"+String(OPCN3Bin20));
    Serial.println("Bin 21 :"+String(OPCN3Bin21));
    Serial.println("Bin 22 :"+String(OPCN3Bin22));
    Serial.println("Bin 23 :"+String(OPCN3Bin23));
    Serial.println("PM 1    :"+String(OPCN3PM1));
    Serial.println("PM 2.5  :"+String(OPCN3PM2_5));
    Serial.println("PM 10   :"+String(OPCN3PM10));
    Serial.println("Temperature  :"+String(OPCN3Temperature));
    Serial.println("Humidity     :"+String(OPCN3Humidity));
    Serial.println("Sampling Time:"+String(OPCN3SamplingTime));
    Serial.println("Power:"+String(Get_Int_From_Bytes_16_Bit(Alpha_Readings,82)));

   if(Get_Int_From_Bytes_16_Bit(Alpha_Readings,82) >= 500){
    OPCN3_Online = true;
     // Put all the pack functions here
    OPCN3_Bin_0.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin0),Get_Current_Time_SD(now),String(OPCN3Bin0));
    OPCN3_Bin_1.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin1),Get_Current_Time_SD(now),String(OPCN3Bin1));
    OPCN3_Bin_2.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin2),Get_Current_Time_SD(now),String(OPCN3Bin2));
    OPCN3_Bin_3.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin3),Get_Current_Time_SD(now),String(OPCN3Bin3));
    OPCN3_Bin_4.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin4),Get_Current_Time_SD(now),String(OPCN3Bin4));
    OPCN3_Bin_5.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin5),Get_Current_Time_SD(now),String(OPCN3Bin5));
    OPCN3_Bin_6.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin6),Get_Current_Time_SD(now),String(OPCN3Bin6));
    OPCN3_Bin_7.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin7),Get_Current_Time_SD(now),String(OPCN3Bin7));
    OPCN3_Bin_8.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin8),Get_Current_Time_SD(now),String(OPCN3Bin8));
    OPCN3_Bin_9.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin9),Get_Current_Time_SD(now),String(OPCN3Bin9));
    OPCN3_Bin_10.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin10),Get_Current_Time_SD(now),String(OPCN3Bin10));
    OPCN3_Bin_11.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin11),Get_Current_Time_SD(now),String(OPCN3Bin11));
    OPCN3_Bin_12.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin12),Get_Current_Time_SD(now),String(OPCN3Bin12));
    OPCN3_Bin_13.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin13),Get_Current_Time_SD(now),String(OPCN3Bin13));
    OPCN3_Bin_14.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin14),Get_Current_Time_SD(now),String(OPCN3Bin14));
    OPCN3_Bin_15.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin15),Get_Current_Time_SD(now),String(OPCN3Bin15));
    OPCN3_Bin_16.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin16),Get_Current_Time_SD(now),String(OPCN3Bin16));
    OPCN3_Bin_17.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin17),Get_Current_Time_SD(now),String(OPCN3Bin17));
    OPCN3_Bin_18.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin18),Get_Current_Time_SD(now),String(OPCN3Bin18));
    OPCN3_Bin_19.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin19),Get_Current_Time_SD(now),String(OPCN3Bin19));
    OPCN3_Bin_20.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin20),Get_Current_Time_SD(now),String(OPCN3Bin20));
    OPCN3_Bin_21.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin21),Get_Current_Time_SD(now),String(OPCN3Bin21));
    OPCN3_Bin_22.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin22),Get_Current_Time_SD(now),String(OPCN3Bin22));
    OPCN3_Bin_23.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3Bin23),Get_Current_Time_SD(now),String(OPCN3Bin23));

    OPCN3_PM_1.Pack(Get_Current_Time_HEX(now),Float_32_to_Hex(&OPCN3PM1),Get_Current_Time_SD(now),String(OPCN3PM1));
    OPCN3_PM_2_5.Pack(Get_Current_Time_HEX(now),Float_32_to_Hex(&OPCN3PM2_5),Get_Current_Time_SD(now),String(OPCN3PM2_5));
    OPCN3_PM_10.Pack(Get_Current_Time_HEX(now),Float_32_to_Hex(&OPCN3PM10),Get_Current_Time_SD(now),String(OPCN3PM10));
    OPCN3_Sampling_Time.Pack(Get_Current_Time_HEX(now),Int_16_to_Hex(&OPCN3SamplingTime),Get_Current_Time_SD(now),String(OPCN3SamplingTime));


    Write_Data_To_SD_BW(OPCN3_Bin_0.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_1.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_2.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_3.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_4.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_5.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_6.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_7.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_8.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_9.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_10.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_11.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_12.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_13.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_14.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_15.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_16.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_17.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_18.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_19.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_20.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_21.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_22.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Bin_23.Get_SD_Data());

    Write_Data_To_SD_BW(OPCN3_PM_1.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_PM_2_5.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_PM_10.Get_SD_Data());
    Write_Data_To_SD_BW(OPCN3_Sampling_Time.Get_SD_Data());

   return true;}
    else{
    OPCN3_Online = false;
    return false;
    }
}




bool Read_PM_Only_OPCN3_BW() {
    byte Alpha_Readings[14];

    beginTransfer();

    if (!transferUntilMatch(0x32, 0xf3, 1000)) {
        Serial.println("Histogram command failed.");
        return false;
    }

    delay(10);

    for (int i = 0; i<14; i++){
        Alpha_Readings[i] = transfer(0x32);
        delayMicroseconds(10);
    }

    endTransfer();

    if(!(Alpha_Readings[0]== 0x00)){
    return true;
    Serial.println("Resetting Histogram");

    }
    else{
    return false;
    }
}

















bool Adafruit_BMP280::begin(uint8_t a, uint8_t chipid) {
  _i2caddr = a;

  if (_cs == -1) {
    // i2c
    Wire.begin();
  } else {
    digitalWrite(_cs, HIGH);
    pinMode(_cs, OUTPUT);

    if (_sck == -1) {
      // hardware SPI
      SPI.begin();
    } else {
      // software SPI
      pinMode(_sck, OUTPUT);
      pinMode(_mosi, OUTPUT);
      pinMode(_miso, INPUT);
    }
  }

  if (read8(BMP280_REGISTER_CHIPID) != chipid)
    return false;

  readCoefficients();
  // write8(BMP280_REGISTER_CONTROL, 0x3F); /* needed? */
  setSampling();
  delay(100);
  return true;
}

void Adafruit_BMP280::setSampling(sensor_mode mode,
		 sensor_sampling   tempSampling,
		 sensor_sampling   pressSampling,
		 sensor_filter     filter,
		 standby_duration  duration) {
     _measReg.mode     = mode;
    _measReg.osrs_t   = tempSampling;
    _measReg.osrs_p   = pressSampling;

    _configReg.filter = filter;
    _configReg.t_sb   = duration;

    write8(BMP280_REGISTER_CONFIG, _configReg.get());
    write8(BMP280_REGISTER_CONTROL, _measReg.get());
}

uint8_t Adafruit_BMP280::spixfer(uint8_t x) {
  if (_sck == -1)
    return SPI.transfer(x);

  // software spi
  //Serial.println("Software SPI");
  uint8_t reply = 0;
  for (int i=7; i>=0; i--) {
    reply <<= 1;
    digitalWrite(_sck, LOW);
    digitalWrite(_mosi, x & (1<<i));
    digitalWrite(_sck, HIGH);
    if (digitalRead(_miso))
      reply |= 1;
  }
  return reply;
}

/**************************************************************************/
/*!
    @brief  Writes an 8 bit value over I2C/SPI
*/
/**************************************************************************/
void Adafruit_BMP280::write8(byte reg, byte value)
{
  if (_cs == -1) {
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.write((uint8_t)value);
    Wire.endTransmission();
  } else {
    if (_sck == -1)
      SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs, LOW);
    spixfer(reg & ~0x80); // write, bit 7 low
    spixfer(value);
    digitalWrite(_cs, HIGH);
    if (_sck == -1)
      SPI.endTransaction();              // release the SPI bus
  }
}

/**************************************************************************/
/*!
    @brief  Reads an 8 bit value over I2C/SPI
*/
/**************************************************************************/
uint8_t Adafruit_BMP280::read8(byte reg)
{
  uint8_t value;

  if (_cs == -1) {
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)_i2caddr, (byte)1);
    value = Wire.read();

  } else {
    if (_sck == -1)
      SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs, LOW);
    spixfer(reg | 0x80); // read, bit 7 high
    value = spixfer(0);
    digitalWrite(_cs, HIGH);
    if (_sck == -1)
      SPI.endTransaction();              // release the SPI bus
  }
  return value;
}

/**************************************************************************/
/*!
    @brief  Reads a 16 bit value over I2C/SPI
*/
/**************************************************************************/
uint16_t Adafruit_BMP280::read16(byte reg)
{
  uint16_t value;

  if (_cs == -1) {
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)_i2caddr, (byte)2);
    value = (Wire.read() << 8) | Wire.read();

  } else {
    if (_sck == -1)
      SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs, LOW);
    spixfer(reg | 0x80); // read, bit 7 high
    value = (spixfer(0) << 8) | spixfer(0);
    digitalWrite(_cs, HIGH);
    if (_sck == -1)
      SPI.endTransaction();              // release the SPI bus
  }

  return value;
}

uint16_t Adafruit_BMP280::read16_LE(byte reg) {
  uint16_t temp = read16(reg);
  return (temp >> 8) | (temp << 8);

}

/**************************************************************************/
/*!
    @brief  Reads a signed 16 bit value over I2C/SPI
*/
/**************************************************************************/
int16_t Adafruit_BMP280::readS16(byte reg)
{
  return (int16_t)read16(reg);

}

int16_t Adafruit_BMP280::readS16_LE(byte reg)
{
  return (int16_t)read16_LE(reg);

}


/**************************************************************************/
/*!
    @brief  Reads a 24 bit value over I2C/SPI
*/
/**************************************************************************/
uint32_t Adafruit_BMP280::read24(byte reg)
{
  uint32_t value;

  if (_cs == -1) {
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)_i2caddr, (byte)3);

    value = Wire.read();
    value <<= 8;
    value |= Wire.read();
    value <<= 8;
    value |= Wire.read();

  } else {
    if (_sck == -1)
      SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs, LOW);
    spixfer(reg | 0x80); // read, bit 7 high

    value = spixfer(0);
    value <<= 8;
    value |= spixfer(0);
    value <<= 8;
    value |= spixfer(0);

    digitalWrite(_cs, HIGH);
    if (_sck == -1)
      SPI.endTransaction();              // release the SPI bus
  }

  return value;
}

/**************************************************************************/
/*!
    @brief  Reads the factory-set coefficients
*/
/**************************************************************************/
void Adafruit_BMP280::readCoefficients(void)
{
    _bmp280_calib.dig_T1 = read16_LE(BMP280_REGISTER_DIG_T1);
    _bmp280_calib.dig_T2 = readS16_LE(BMP280_REGISTER_DIG_T2);
    _bmp280_calib.dig_T3 = readS16_LE(BMP280_REGISTER_DIG_T3);

    _bmp280_calib.dig_P1 = read16_LE(BMP280_REGISTER_DIG_P1);
    _bmp280_calib.dig_P2 = readS16_LE(BMP280_REGISTER_DIG_P2);
    _bmp280_calib.dig_P3 = readS16_LE(BMP280_REGISTER_DIG_P3);
    _bmp280_calib.dig_P4 = readS16_LE(BMP280_REGISTER_DIG_P4);
    _bmp280_calib.dig_P5 = readS16_LE(BMP280_REGISTER_DIG_P5);
    _bmp280_calib.dig_P6 = readS16_LE(BMP280_REGISTER_DIG_P6);
    _bmp280_calib.dig_P7 = readS16_LE(BMP280_REGISTER_DIG_P7);
    _bmp280_calib.dig_P8 = readS16_LE(BMP280_REGISTER_DIG_P8);
    _bmp280_calib.dig_P9 = readS16_LE(BMP280_REGISTER_DIG_P9);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
float Adafruit_BMP280::readTemperature(void)
{
  int32_t var1, var2;

  int32_t adc_T = read24(BMP280_REGISTER_TEMPDATA);
  adc_T >>= 4;

  var1  = ((((adc_T>>3) - ((int32_t)_bmp280_calib.dig_T1 <<1))) *
	   ((int32_t)_bmp280_calib.dig_T2)) >> 11;

  var2  = (((((adc_T>>4) - ((int32_t)_bmp280_calib.dig_T1)) *
	     ((adc_T>>4) - ((int32_t)_bmp280_calib.dig_T1))) >> 12) *
	   ((int32_t)_bmp280_calib.dig_T3)) >> 14;

  t_fine = var1 + var2;

  float T  = (t_fine * 5 + 128) >> 8;
  return T/100;
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
float Adafruit_BMP280::readPressure(void) {
  int64_t var1, var2, p;

  // Must be done first to get the t_fine variable set up
  readTemperature();

  int32_t adc_P = read24(BMP280_REGISTER_PRESSUREDATA);
  adc_P >>= 4;

  var1 = ((int64_t)t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)_bmp280_calib.dig_P6;
  var2 = var2 + ((var1*(int64_t)_bmp280_calib.dig_P5)<<17);
  var2 = var2 + (((int64_t)_bmp280_calib.dig_P4)<<35);
  var1 = ((var1 * var1 * (int64_t)_bmp280_calib.dig_P3)>>8) +
    ((var1 * (int64_t)_bmp280_calib.dig_P2)<<12);
  var1 = (((((int64_t)1)<<47)+var1))*((int64_t)_bmp280_calib.dig_P1)>>33;

  if (var1 == 0) {
    return 0;  // avoid exception caused by division by zero
  }
  p = 1048576 - adc_P;
  p = (((p<<31) - var2)*3125) / var1;
  var1 = (((int64_t)_bmp280_calib.dig_P9) * (p>>13) * (p>>13)) >> 25;
  var2 = (((int64_t)_bmp280_calib.dig_P8) * p) >> 19;

  p = ((p + var1 + var2) >> 8) + (((int64_t)_bmp280_calib.dig_P7)<<4);
  return (float)p/256;
}

float Adafruit_BMP280::readAltitude(float seaLevelhPa) {
  float altitude;

  float pressure = readPressure(); // in Si units for Pascal
  pressure /= 100;

  altitude = 44330 * (1.0 - pow(pressure / seaLevelhPa, 0.1903));

  return altitude;
}

/**************************************************************************/
/*!
    @brief  Take a new measurement (only possible in forced mode)
    !!!todo!!!
*/
/**************************************************************************/
/*
void Adafruit_BMP280::takeForcedMeasurement()
{
    // If we are in forced mode, the BME sensor goes back to sleep after each
    // measurement and we need to set it to forced mode once at this point, so
    // it will take the next measurement and then return to sleep again.
    // In normal mode simply does new measurements periodically.
    if (_measReg.mode == MODE_FORCED) {
        // set to forced mode, i.e. "take next measurement"
        write8(BMP280_REGISTER_CONTROL, _measReg.get());
        // wait until measurement has been completed, otherwise we would read
        // the values from the last measurement
        while (read8(BMP280_REGISTER_STATUS) & 0x08)
		delay(1);
    }
}
*/
