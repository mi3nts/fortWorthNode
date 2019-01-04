# import serial
# ser = serial.Serial('/dev/ttyACM3')
import serial
import datetime
import os
import csv

dataFolder = "/media/teamlary/Team_Lary_1/gitGubRepos/data/mintsData/"

def main():

    ser = serial.Serial(
    port='/dev/ttyACM1',\
    baudrate=9600,\
    parity  =serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
    timeout=0)

    print("connected to: " + ser.portstr)

    #this will store the line
    line = []

    while True:
        for c in ser.read():
            line.append(chr(c))
            if chr(c) == '-':
                dataString     = (''.join(line))
                dataStringPost = dataString.replace('-', '')
                dataSplit(dataStringPost,datetime.datetime.now())
                line = []
                break

    ser.close()
        # if chr(c) == '-':
        #     print(''.join(line))

def dataSplit(dataString,dateTime):
    dataOut   = dataString.split('!')
    if(len(dataOut) == 2):
        tag       = dataOut[0]
        dataQuota = dataOut[1]
        if(tag.find("#mintsO")==0):
            sensorSplit(dataQuota,dateTime)

def sensorSplit(dataQuota,dateTime):
    dataOut    = dataQuota.split('>')
    if(len(dataOut) == 2):
        sensorID   = dataOut[0]
        sensorData = dataOut[1]
        sensorSend(sensorID,sensorData,dateTime)
        # print("Sensor ID  : "+sensorID)
        # print("Sensor Data: "+sensorData)
        # print("Date Time : " +str(dateTime))



def sensorSend(sensorID,sensorData,dateTime):
    if(sensorID=="HTU21D"):
        HTU21DWrite(sensorData,dateTime)
    if(sensorID=="BMP280"):
        BMP280Write(sensorData,dateTime)
    if(sensorID=="OPCN3"):
        OPCN3Write(sensorData,dateTime)

def HTU21DWrite(sensorData,dateTime):
    dataOut    = sensorData.split(':')
    sensorName = "HTU21D"
    dataLength = 2
    if(len(dataOut) ==(dataLength +1)):
        sensorDictionary = {
                "dateTime"           : str(dateTime),
        		"temperature" :dataOut[0],
            	"humdity"     :dataOut[1],
        	     }


    #Getting Write Path
    writePath = getWritePath(sensorName,dateTime)
    exists = directoryCheck(writePath)
    writeCSV2(writePath,sensorDictionary,exists)
    # print(writePath)
    print(sensorDictionary)
#
def BMP280Write(sensorData,dateTime):
    dataOut    = sensorData.split(':')
    sensorName = "BMP280"
    dataLength = 2
    if(len(dataOut) == (dataLength +1)):
        sensorDictionary = {
                "dateTime"           : str(dateTime),
        		"temperature"  :dataOut[0],
            	"pressure"     :dataOut[1],
        	     }

    #Getting Write Path
    writePath = getWritePath(sensorName,dateTime)
    exists = directoryCheck(writePath)
    writeCSV2(writePath,sensorDictionary,exists)
    # print(writePath)
    print(sensorDictionary)


def OPCN3Write(sensorData,dateTime):
    dataOut    = sensorData.split(':')
    sensorName = "OPCN3"
    dataLength=43
    if(len(dataOut) == (dataLength +1)):
        sensorDictionary = {
                "dateTime"    :str(dateTime),
        		"valid"       :dataOut[0],
            	"binCount0"   :dataOut[1],
            	"binCount1"   :dataOut[2],
            	"binCount2"   :dataOut[3],
            	"binCount3"   :dataOut[4],
            	"binCount4"   :dataOut[5],
            	"binCount5"   :dataOut[6],
            	"binCount6"   :dataOut[7],
            	"binCount7"   :dataOut[8],
            	"binCount8"   :dataOut[9],
            	"binCount9"   :dataOut[10],
            	"binCount10"  :dataOut[11],
            	"binCount11"  :dataOut[12],
            	"binCount12"  :dataOut[13],
            	"binCount13"  :dataOut[14],
            	"binCount14"  :dataOut[15],
            	"binCount15"  :dataOut[16],
            	"binCount16"  :dataOut[17],
            	"binCount17"  :dataOut[18],
            	"binCount18"  :dataOut[19],
            	"binCount19"  :dataOut[20],
            	"binCount20"  :dataOut[21],
            	"binCount21"  :dataOut[22],
            	"binCount22"  :dataOut[23],
            	"binCount23"  :dataOut[24],
                "bin1TimeToCross"      :dataOut[25],
                "bin3TimeToCross"      :dataOut[26],
                "bin5TimeToCross"      :dataOut[27],
                "bin7TimeToCross"      :dataOut[28],
                "samplingPeriod"       :dataOut[29],
                "sampleFlowRate"       :dataOut[30],
                "temperature"          :str(float(dataOut[31])/1000),
                "humidity"             :str(float(dataOut[32])/500),
                "pm1,2"                :dataOut[33],
                "pm2_5,2"              :dataOut[34],
                "pm10,2"               :dataOut[35],
                "rejectCountGlitch"    :dataOut[36],
                "rejectCountLongTOF"   :dataOut[37],
                "rejectCountRatio"     :dataOut[38],
                "rejectCountOutOfRange":dataOut[39],
                "fanRevCount"          :dataOut[40],
                "laserStatus"          :dataOut[41],
                "checkSum"             :dataOut[42],

             }
    #Getting Write Path
    writePath = getWritePath(sensorName,dateTime)
    exists = directoryCheck(writePath)
    writeCSV2(writePath,sensorDictionary,exists)
    # print(writePath)
    print(sensorDictionary)

def writeCSV2(writePath,sensorDictionary,exists):
    keys =  list(sensorDictionary.keys())
    with open(writePath, 'a') as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=keys)
        # print(exists)
        if(not(exists)):
            writer.writeheader()
        writer.writerow(sensorDictionary)



def getWritePath(labelIn,dateTime):
    writePath = dataFolder +str(dateTime.year).zfill(4)  + "/" + str(dateTime.month).zfill(2)  +"/mintsO"+ labelIn + str(dateTime.year).zfill(4)  + str(dateTime.month).zfill(2)  + str(dateTime.day).zfill(2)  + ".csv"
    return writePath;

def getListDictionaryFromPath(dirPath):
    print("Reading : "+ dirPath)
    reader = csv.DictReader(open(dirPath))
    reader = list(reader)

def fixCSV(keyIn,valueIn,currentDictionary):
    editedList       = editDictionaryList(currentDictionary,keyIn,valueIn)
    return editedList

def editDictionaryList(dictionaryListIn,keyIn,valueIn):
    for dictionaryIn in dictionaryListIn:
        dictionaryIn[keyIn] = valueIn

    return dictionaryListIn

def getDateDataOrganized(currentCSV,nodeID):
    currentCSVName = os.path.basename(currentCSV)
    nameOnly = currentCSVName.split('-Organized.')
    dateOnly = nameOnly[0].split(nodeID+'-')
    print(dateOnly)
    dateInfo = dateOnly[1].split('-')
    print(dateInfo)
    return dateInfo


def getFilePathsforOrganizedNodes(nodeID,subFolder):
    nodeFolder = subFolder+ nodeID+'/';
    pattern = "*Organized.csv"
    fileList = [];
    for path, subdirs, files in os.walk(nodeFolder):
        for name in files:
            if fnmatch(name, pattern):
                fileList.append(os.path.join(path, name))
    return sorted(fileList)


def getLocationList(directory, suffix=".csv"):
    filenames = listdir(directory)
    dateList = [ filename for filename in filenames if filename.endswith( suffix ) ]
    return sorted(dateList)


def getListDictionaryCSV(inputPath):
    # the path will depend on the node ID
    reader = csv.DictReader(open(inputPath))
    reader = list(reader)
    return reader

def writeCSV(reader,keys,outputPath):
    directoryCheck(outputPath)
    csvWriter(outputPath,reader,keys)

def directoryCheck(outputPath):
    exists = os.path.isfile(outputPath)
    directoryIn = os.path.dirname(outputPath)
    if not os.path.exists(directoryIn):
        os.makedirs(directoryIn)
    return exists

def csvWriter(writePath,organizedData,keys):
    with open(writePath,'w') as output_file:
        writer = csv.DictWriter(output_file, fieldnames=keys)
        writer.writeheader()
        writer.writerows(organizedData)


def gainDirectoryInfo(dailyDownloadLocation):
    directoryPaths = []
    directoryNames = []
    directoryFiles = []
    for (dirpath, dirnames, filenames) in walk(dailyDownloadLocation):
        directoryPaths.extend(dirpath)
        directoryNames.extend(dirnames)
        directoryFiles.extend(filenames)

    return directoryPaths,directoryNames,directoryFiles;

if __name__ == "__main__":
   main()
