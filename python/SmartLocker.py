from BLEcontroller import BLEcontroller
from bluepy.btle import *
from time import sleep

class SmartLoker():
    def __init__(self,openParam=1000,closeParam=2000):
        self.close_comm         = 0
        self.open_comm          = 1
        self.close_param_comm   = 2
        self.open_param_comm    = 3

        self.openParameter = openParam
        self.closeParameter = closeParam

        self.ble = BLEcontroller("00:1e:c0:4a:29:6d",ADDR_TYPE_PUBLIC)
        
        self.ble.setService("SmartLoker",'3A41CCA5-A1F9-4690-9D5E-11A946BAFCB4')
        
        self.ble.setCharacteristic("servo_command",'E3C8A262-03AC-447F-9FDB-F8FED75EE00F')
        self.ble.setCharacteristic("servo_param"  ,'EB57140A-3540-4A6D-8C97-40D75DF4CBEF')
        self.ble.setCharacteristic("status"       ,'A57CB712-3FD3-4075-9F92-528225EE04BE')

        self.ble.connect()

        # switch servo definitation
        # 0: close
        # 1: open
        # 2: set open parameter
        # 3: set close parameter
        
        # setting sequense
        # 1. write open parameters
        # 2. write No.2 to switch servo characteristic to store open parameter in device
        # 3. compare whether the transmitted parameter is the same as the value received from status characteristic
        # 4. write close parameters
        # 5. write No.3 to switch servo characteristic to store close parameter in device
        # 6. compare whether the transmitted parameter is the same as the value received from status characteristic
        # 7. write No.0 to switch servo characteristic
        
        #Write paramter to device to set parameter when locker open
        self.ble.write("short","servo_param",self.openParameter)
        self.ble.write("byte","servo_command",self.open_param_comm)
        #Check to parameter wrote by received parameter
        response = self.ble.read("short","status")
        if(response == self.openParameter):
            print("Success to set open paramter. wrote paramter:[%d] response from device:[%d]" % (self.openParameter,response))
        else:
            print("Faild set parameter %d" % response)

        #Write paramter to device to set parameter when locker close
        self.ble.write("short","servo_param",self.closeParameter)
        self.ble.write("byte","servo_command",self.close_param_comm)
        #Check to parameter wrote by received parameter
        response = self.ble.read("short","status")
        if(response == self.closeParameter):
            print("Success to set close paramter. wrote paramter:[%d] response from device:[%d]" % (self.closeParameter,response))
        else:
            print("Faild set parameter %d" % response)

        self.ble.write("byte","servo_command",self.close_comm)


    def getServoStatus(self):
        response = self.ble.read("short","status")
        if(response == self.openParameter):
            return True
        else: 
            return False
    
    def operateServo(self,boolean=False):
        if(boolean is True):
            self.ble.write("byte","switch_servo",self.open_comm)
        else:
            self.ble.write("byte","switch_servo",self.close_comm)
        

if __name__ == '__main__':
    locker = SmartLoker( )
    i = 0
    try:
        pass
        # while True:
        #     pass
    except KeyboardInterrupt:
        exit()
    