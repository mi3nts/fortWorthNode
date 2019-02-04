# GIS Node

## Introduction 
The current repo introduces a device which is inteneded to be portable particulate matter sensor. The device and its software  is meant to be designed, implemented and deployed in an expeditive manner. As such, most aspects of both the hardware and  the software is kept simple and is easilly expandable to make way for more sensors to be added. The production is a miniature version of [MINTS Central Node](https://github.com/mi3nts/centralNode).

### Design Specifications  

1. Node Brain:
- [Odroid XU4](https://ameridroid.com/products/odroid-xu4): The XU4 runs on a Linux platform. 

2. Sensor Hub:
- [Arduino Due](https://store.arduino.cc/usa/arduino-due): The Sensor Hub is ran on an Arduino Platform. 

3. Primary Sensor:
- [Alpha Sense OPC-N3](http://www.alphasense.com/WEB1213/wp-content/uploads/2018/02/OPC-N3.pdf): Measures pm1, pm2.5, pm10, temperature, humidity and Particulate Matter distribution with 24 bins from 0.35um to 40um in diametor.  

4. Secondary Sensors: 
- [BME 280](http://wiki.seeedstudio.com/Grove-Barometer_Sensor-BME280/): measures Temprature, Humidity, Pressure 
- [UBLOX GPS](https://www.amazon.com/Waterproof-Navigator-Automobile-Navigation-Compatible/dp/B071XY4R26/ref=asc_df_B071XY4R26/?tag=hyprod-20&linkCode=df0&hvadid=312129973570&hvpos=1o4&hvnetw=g&hvrand=10149593131629630592&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9026945&hvtargid=pla-378730411150&psc=1): measures Latitude, Longitude, Altitude, DateTime and Speed. 

5. Power :
- [Rawpower Portable Battery](https://www.amazon.com/RAVPower-10000mAh-Ultra-Slim-High-Density-Li-Polymer/dp/B077CZ8412/ref=sr_1_8?ie=UTF8&qid=1549294766&sr=8-8&keywords=portable+charger&refinements=p_89%3ARAVPower): Quick Charge 3.0 RAVPower 10000mAh Portable Charger  

6. Onboard Data Storage: 
- The device contains an onbaord SD card. Can store upto 24(hours)*250(days) of data.  

7. Data Output: 
-  Data is streamed to a server at University of Texas at Dallas through [Wi-Fi](https://ameridroid.com/products/wifi-module-0)(when available) or via the onboard ethernet port on the XU4. 
