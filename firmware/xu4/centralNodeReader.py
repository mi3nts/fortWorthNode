# import serial
# ser = serial.Serial('/dev/ttyACM3')
import serial

ser = serial.Serial(
    port='/dev/ttyACM0',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
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
            lk = (''.join(line))
            lk1 = lk.replace('-', '')
            print(lk1)

            line = []
            break

ser.close()
    # if chr(c) == '-':
    #     print(''.join(line))
    #     line = []
    #     break
