import sys
sys.path.append('../')

from context import Screen, ScreenContext
import atexit
import datetime
import time
import serial
import datetime
import os
import csv
import deepdish as dd
import time
import uuid
import subprocess
from getmac import get_mac_address
from mintsXU4 import mintsLatest as mL
from mintsXU4 import mintsDefinitions as mD




dataFolder = mD.dataFolder
ctx = ScreenContext(mD.show2Port)
atexit.register(ctx.cleanup)
macAddress = mD.macAddress




def main():


    preVal = "-----"
    pm1  = preVal
    pm2_5= preVal
    pm10 = preVal
    temperature= preVal
    humidity= preVal
    radiationValue= preVal
    pressure= preVal

    printEmpty()
    printIntro()
    time.sleep(4)
    printEmpty()
    while True:

        data,valid    = mL.readHDF5LatestData("OPCN3","pm1")
        if(valid):
            pm1 = data

        data,valid    = mL.readHDF5LatestData("OPCN3","pm2_5")
        if(valid):
            pm2_5  = data

        data,valid    = mL.readHDF5LatestData("OPCN3","pm10")
        if(valid):
            pm10  = data

        data,valid    = mL.readHDF5LatestData("HTU21D","temperature")
        if(valid):
            temperature  = data

        data,valid    = mL.readHDF5LatestData("BMP280","pressure")
        if(valid):
            pressure  = data

        data,valid    = mL.readHDF5LatestData("HTU21D","humidity")
        if(valid):
            humidity  = data

        data,valid    = mL.readHDF5LatestData("LIBRAD","radiationValue")
        if(valid):
            radiationValue  = data

        printData(pm1,pm2_5,pm10,temperature,pressure,humidity,radiationValue)

def printEmpty():
    ctx.fg_color(Screen.RED).write("").home()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("").home()


def printIntro():
    ctx.fg_color(Screen.RED).write("").home()
    ctx.fg_color(Screen.WHITE).write("----------MINTS----------").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("-------------------------").linebreak()
    ctx.fg_color(Screen.GREEN).write(" Multi-scale Integrated ").linebreak()
    ctx.fg_color(Screen.GREEN).write(" Sensing and Simulation ").linebreak()
    ctx.fg_color(Screen.GREEN).write("-------------------------").linebreak()
    ctx.fg_color(Screen.BLUE).write ("  http://utdmints.info/  ").linebreak()
    ctx.fg_color(Screen.GREEN).write("-------------------------").linebreak()
    ctx.fg_color(Screen.CYAN).write ("https://github.com/mi3nts").linebreak()
    ctx.fg_color(Screen.GREEN).write("-------------------------").linebreak()
    ctx.fg_color(Screen.WHITE).write("ID:"+macAddress).linebreak()
    ctx.fg_color(Screen.GREEN).write("-------------------------").linebreak()
    ctx.fg_color(Screen.YELLOW).write(time.strftime('%X %x %Z')).linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("----------MINTS----------").linebreak()
    ctx.fg_color(Screen.WHITE).write("").home()

def printData(pm1,pm2_5,pm10,temperature,pressure,humidity,radiationValue):

    ctx.fg_color(Screen.RED).write("").home()
    ctx.fg_color(Screen.WHITE).write("----------MINTS----------").linebreak()
    ctx.fg_color(Screen.WHITE).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("PM1  :" + pm1).linebreak()
    ctx.fg_color(Screen.WHITE).write("PM2.5:" + pm2_5).linebreak()
    ctx.fg_color(Screen.WHITE).write("PM10 :" + pm10).linebreak()
    ctx.fg_color(Screen.WHITE).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("Temperature: "+ temperature+ "C").linebreak()
    ctx.fg_color(Screen.WHITE).write("Pressure   : "+ pressure   +  "Pa").linebreak()
    ctx.fg_color(Screen.WHITE).write("Humidity   : "+ humidity   +  "%").linebreak()
    ctx.fg_color(Screen.WHITE).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("Radiation  : "+ radiationValue + "uSv/h").linebreak()
    ctx.fg_color(Screen.WHITE).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("ID:"+macAddress).linebreak()
    ctx.fg_color(Screen.WHITE).write(time.strftime('%X %x %Z')).linebreak()
    ctx.fg_color(Screen.WHITE).write("----------MINTS----------").linebreak()
    ctx.fg_color(Screen.WHITE).write("").home()
#


if __name__ == "__main__":
   main()
