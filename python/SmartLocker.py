from BLEcontroller import BLEcontroller
from bluepy.btle import *
from time import sleep
import struct

class SmartLoker():
    def __init__(self,openParam=0,closeParam=100):
        self.openParameter = openParam
        self.closeParameter = closeParam

        self.ble = BLEcontroller("00:1e:c0:4a:29:6d",ADDR_TYPE_PUBLIC)
        
        self.ble.setService("SmartLoker",'3A41CCA5-A1F9-4690-9D5E-11A946BAFCB4')
        
        self.ble.setCharacteristic("servo" ,'EB57140A-3540-4A6D-8C97-40D75DF4CBEF')
        self.ble.setCharacteristic("status",'A57CB712-3FD3-4075-9F92-528225EE04BE')

        self.ble.connect()

    def getServoStatus(self):
        tmp = self.ble.read("status")
        print("%d"%tmp)
        if tmp is self.openParameter:
            return True
        else: 
            return False
    
    def operateServo(self,boolean=False):
        if(boolean is True):
            self.ble.write("servo",self.openParameter)
        else:
            self.ble.write("servo",self.closeParameter)


if __name__ == '__main__':
    locker = SmartLoker( )
    i = 0

    try:
        while True:
            locker.ble.write("short","servo",1200)
            print(locker.ble.read("short","status"))
            # locker.operateServo(True)
            # sleep(3)
            # print(locker.getServoStatus())
            # locker.operateServo(False)
            # sleep(3)          
            # print(locker.getServoStatus())

    except KeyboardInterrupt:
        exit()