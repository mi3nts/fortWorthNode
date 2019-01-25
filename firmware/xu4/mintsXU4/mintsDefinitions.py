
from getmac import get_mac_address
import serial.tools.list_ports

def findPort(find):
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        currentPort = str(p)
        if(currentPort.endswith(find)):
            return(currentPort.split(" ")[0])


dataFolder          = "/media/usb/data/mintsData/"
duePort             = findPort("Arduino Due")
nanoPort            = findPort("FT232R USB UART")
show2Port           = findPort("CP2104 USB to UART Bridge Controller")
# macAddress          = get_mac_address(interface="docker0").replace(":","")
macAddress          = get_mac_address(interface="eth0").replace(":","")
