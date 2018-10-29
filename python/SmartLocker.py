from BLEcontroller import BLEcontroller
from bluepy.btle import *
from time import sleep
import struct

class SmartLoker():
    def __init__(self,openParam=1000,closeParam=2000):
        self.close_comm        = 0
        self.open_comm          = 1
        self.close_param_comm   = 2
        self.open_param_comm    = 3

        self.openParameter = openParam
        self.closeParameter = closeParam

        self.ble = BLEcontroller("00:1e:c0:4a:29:6d",ADDR_TYPE_PUBLIC)
        
        self.ble.setService("SmartLoker",'3A41CCA5-A1F9-4690-9D5E-11A946BAFCB4')
        
        self.ble.setCharacteristic("switch_servo",'E3C8A262-03AC-447F-9FDB-F8FED75EE00F')
        self.ble.setCharacteristic("servo_param" ,'EB57140A-3540-4A6D-8C97-40D75DF4CBEF')
        self.ble.setCharacteristic("status"      ,'A57CB712-3FD3-4075-9F92-528225EE04BE')

        self.ble.connect()

        self.ble.write("short","servo_param",self.openParameter)
        self.ble.write("byte","switch_servo",self.open_param_comm)
        response = self.ble.read("short","status")
        if(response is self.openParameter):
            print("success set open paramter[%d] return [%d]" % (self.openParameter,response))
        else:
            print("Faild set parameter %d" % response)

        self.ble.write("short","servo_param",self.closeParameter)
        self.ble.write("byte","switch_servo",self.close_param_comm)
        response = self.ble.read("short","status")
        if(response is self.openParameter):
            print("success set close paramter[%d] return [%d]" % (self.openParameter,response))
        else:
            print("Faild set parameter %d" % response)

        self.ble.write("byte","switch_servo",self.close_comm)


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
            pass
            # locker.ble.write("short","servo",1200)
            # print(locker.ble.read("short","status"))
            # locker.operateServo(True)
            # sleep(3)
            # print(locker.getServoStatus())
            # locker.operateServo(False)
            # sleep(3)          
            # print(locker.getServoStatus())
    except KeyboardInterrupt:
        exit()
    # switch servo
    # 0: close
    # 1: open
    # 2: set open parameter
    # 3: set close parameter
    
    # setting sequense
    # 1. write open parameters
    # 2. write No.2 switch servo characteristic to store open parameter in device
    # 3. compare whether the transmitted parameter is the same as the value received from status characteristic
    # 4. write close parameters
    # 5. write No.3 switch servo characteristic to store close parameter in device
    # 6. compare whether the transmitted parameter is the same as the value received from status characteristic
    # 7. write No.0 switch servo characteristic