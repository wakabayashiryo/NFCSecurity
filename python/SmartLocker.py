from BLEcontroller import BLEcontroller
from bluepy.btle import *
from time import sleep

class SmartLoker():
    def __init__(self,openParam=0,closeParam=100):
        self.openParameter = openParam
        self.closeParameter = closeParam

        self.ble = BLEcontroller("00:1e:c0:4a:29:6d",ADDR_TYPE_PUBLIC)
        
        self.ble.setService("SmartLoker",'3A41CCA5-A1F9-4690-9D5E-11A946BAFCB4')
        
        self.ble.setCharacteristic("sensor",'1713453B-292E-4B1C-9515-F23DDAC2B2B0')
        self.ble.setCharacteristic("servo" ,'EB57140A-3540-4A6D-8C97-40D75DF4CBEF')
        self.ble.setCharacteristic("status",'A57CB712-3FD3-4075-9F92-528225EE04BE')
        self.ble.setCharacteristic("relay" ,'9D9A42B6-EC11-47E2-8B0C-441820EE7032')

        self.ble.connect()

    def getMagneticSensor(self):
        tmp = self.ble.read("sensor")
        print("%d %d " % (tmp,self.ble.read("status")))
        if tmp is 127:
            return True    
        else: 
            return False
    
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

    def operateRalay(self,boolean=False):
        if(boolean is True):
            self.ble.write("relay",127)
        else:
            self.ble.write("relay",0)            

if __name__ == '__main__':
    locker = SmartLoker( )

    try:
        while True:
            locker.operateRalay(True)
            locker.operateServo(True)
            sleep(3)
            print(locker.getServoStatus())
            locker.operateServo(False)
            locker.operateRalay(False)
            sleep(3)          
            print(locker.getServoStatus())

    except KeyboardInterrupt:
        exit()