
import time
from mintsXU4 import mintsLatest as mL

def main():
    while True:
        mL.readHDF5LatestAll("HTU21D")
        time.sleep(1)
        mL.readHDF5LatestAll("BMP280")
        time.sleep(1)
        mL.readHDF5LatestAll("INA219")
        time.sleep(1)
        mL.readHDF5LatestAll("LIBRAD")
        time.sleep(1)
        mL.readHDF5LatestAll("OPCN3")
        time.sleep(1)

if __name__ == "__main__":
   main()
