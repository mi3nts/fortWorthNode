# Central Node

## Introduction 
Portable devices which can detect airbourne particulates are finding its way into current consumer markets. Unlike there bulky, stationary counterparts the small scale nature of such sensors feeds into a more user friendly, hazzle free platform. The current document proposes such a portable device which encorparates an ensemble of IOT sensors .

### Design Specifications  

1. Sensor Brain: [Arduino Due](https://store.arduino.cc/usa/arduino-due)
- The Node will run on the Arduino Platform. 

2. OPC Sensor: 
 - Alhpa Sense OPC-N3 <br/>
   **http://www.alphasense.com/WEB1213/wp-content/uploads/2018/02/OPC-N3.pdf** <br/>      

3. Secondary Sensors: 
- Temprature
- Humidity 
- Pressure 
- GPS 

4. Power :
- Uses between 3W - 12W
- Will be powered through a portable USB Battery that is to be charged via a solar panel.
- Will be equipped with a power sensor to monitor battery level 

5. Date Output: 
- On board OLED  
- The device will send live updates to a google drive doc. 

6. Onbaord  Date Storage: 
- The device contains an onbaord SD card 

7 - Web Connectivity:
- The node will have a hardwired internet connection via a RJ45, Ethernet cable.

8. Weight:
- 1.5 Kg



