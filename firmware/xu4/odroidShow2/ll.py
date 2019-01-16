from context import Screen, ScreenContext
import atexit
import datetime
import time

# import serial
# ser = serial.Serial('/dev/ttyACM3')
import serial
import datetime
import os
import csv
import deepdish as dd
import time
import uuid
import subprocess
from getmac import get_mac_address


dataFolder = "/media/teamlary/Team_Lary_1/gitGubRepos/data/mintsData/"
ctx = ScreenContext("/dev/ttyUSB0")
atexit.register(ctx.cleanup)
macAddress = get_mac_address(interface="docker0")

def main():

    printEmpty()
    printIntro()
    time.sleep(4)
    printEmpty()
    while True:
        printData()


def readHDF5LatestAll(sensorName):
    print(str(datetime.datetime.now()))
    try:
        d = dd.io.load(dataFolder+sensorName+".h5")
        return d
    except:
        print("This is an error message!")
        return "--"

def readHDF5LatestData(sensorName,keyIn):
    print(str(datetime.datetime.now()))
    try:
        d = dd.io.load(dataFolder+sensorName+".h5")
        return str(d[keyIn])
    except:
        print("This is an error message!")
        return "--"

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

def printData():

    pm1         = readHDF5LatestData("OPCN3","pm1")
    pm2_5       = readHDF5LatestData("OPCN3","pm2_5")
    pm10        = readHDF5LatestData("OPCN3","pm10")

    temperature = readHDF5LatestData("HTU21D","temperature")
    pressure    = readHDF5LatestData("BMP280","pressure")
    humidity    = readHDF5LatestData("HTU21D","humidity")


    ctx.fg_color(Screen.RED).write("").home()
    ctx.fg_color(Screen.WHITE).write("----------MINTS----------").linebreak()
    ctx.fg_color(Screen.WHITE).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("PM1  :" + pm1).linebreak()
    ctx.fg_color(Screen.WHITE).write("PM2.5:" + pm2_5).linebreak()
    ctx.fg_color(Screen.WHITE).write("PM10 :" + pm10).linebreak()
    ctx.fg_color(Screen.WHITE).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("Temperature: "+ temperature).linebreak()
    ctx.fg_color(Screen.WHITE).write("Pressure   : "+ pressure).linebreak()
    ctx.fg_color(Screen.WHITE).write("Humidity   : "+ humidity).linebreak()
    ctx.fg_color(Screen.WHITE).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("ID:"+macAddress).linebreak()
    ctx.fg_color(Screen.WHITE).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write(time.strftime('%X %x %Z')).linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("----------MINTS----------").linebreak()
    ctx.fg_color(Screen.WHITE).write("").home()



if __name__ == "__main__":
   main()
