
from getmac import get_mac_address

dataFolder          = "/media/teamlary/Team_Lary_1/gitGubRepos/data/mintsData/"
duePort             = "/dev/ttyACM1"
nanoPort            = "/dev/ttyUSB1"
show2Port           = "/dev/ttyUSB0"
macAddress          = get_mac_address(interface="docker0").replace(":","")
