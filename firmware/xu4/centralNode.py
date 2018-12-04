# from datetime import timezone
import time
import os
# import datetime
# import numpy as np
# import pickle
# from skimage import io, color
# import cv2
# import gspread
# from oauth2client.service_account import ServiceAccountCredentials
import serial


def main():

    global ser
    print("Mints - Multi-scale Integrated Sensing and Simulation")
    ser = serial.Serial('/dev/ttyACM0', 9600)
    command = input("Print Command: ")
    print("Command: ", command)
    print(type(command))
    toSend = bytes(command,"ascii")
    print(toSend)
    # sendData(toSend)

def timeTaken(message,start):
    print(message+str(time.time()-start)+' Seconds')


def gzExtractor(gzLocation):
    os.system('gzip -f ' +gzLocation)

def sendData(data):

    ser.write(data)



if __name__ == "__main__":
   main()
