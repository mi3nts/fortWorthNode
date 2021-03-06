from datetime import timezone
import time
import os
import datetime
import netifaces as ni
from collections import OrderedDict
import netifaces as ni
from requests import get

from mintsXU4 import mintsSensorReader as mSR
from mintsXU4 import mintsDefinitions  as mD

dataFolder = mD.dataFolder



def findLocalIP():
    try:
        localIp = ni.ifaddresses('eth0')[ni.AF_INET][0]['addr'] # XU4
        return localIp
    except:
        print("Not The XU4")

    try:
        localIp  = ni.ifaddresses('docker0')[ni.AF_INET][0]['addr'] # Lab Machine
        return localIp
    except:
        print("Not The PC")
    return "xxxxxxxx"



def main():

    sensorName = "IP"
    dateTimeNow = datetime.datetime.now()
    publicIp = get('https://api.ipify.org').text
    localIp = findLocalIP()



    sensorDictionary =  OrderedDict([
            ("dateTime"     , str(dateTimeNow)),
            ("publicIp"  ,str(publicIp)),
            ("localIp"  ,str(localIp))
            ])

    mSR.sensorFinisherIP(dateTimeNow,sensorName,sensorDictionary)

if __name__ == "__main__":
   main()
