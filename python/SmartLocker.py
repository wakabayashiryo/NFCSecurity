from BLEcontroller import BLEcontroller

class SmartLocker():
    def __init__(self,openParam=1000,closeParam=2000):
        self.close_comm         = 0
        self.open_comm          = 1
        self.close_param_comm   = 2
        self.open_param_comm    = 3
        self.idle_comm          = 4

        self.openParameter = openParam
        self.closeParameter = closeParam

        self.ble = BLEcontroller("00:1e:c0:4a:29:6d","public")
        
        self.ble.setService("SmartLoker",'3A41CCA5-A1F9-4690-9D5E-11A946BAFCB4')
        
        self.ble.setCharacteristic("servo_command",'E3C8A262-03AC-447F-9FDB-F8FED75EE00F')
        self.ble.setCharacteristic("servo_param"  ,'EB57140A-3540-4A6D-8C97-40D75DF4CBEF')
        self.ble.setCharacteristic("status"       ,'A57CB712-3FD3-4075-9F92-528225EE04BE')

        self.ble.connect()

        self.setParameterWhenOpen (openParam)
        self.setParameterWhenClose(closeParam)

    def getServoStatus(self):
        response = self.ble.read("short","status")
        if(response == self.openParameter):
            return 'open'
        elif(response == self.closeParameter): 
            return 'close'
        else:
            return 'error'

    def operateServo(self,operate):
        if(operate is 'open'):
            self.ble.write("byte","servo_command",self.open_comm)
        elif(operate is 'close'):
            self.ble.write("byte","servo_command",self.close_comm)
        else:
            return 'error'

        self.ble.write("byte","servo_command",self.idle_comm)
            
    def setParameterWhenOpen(self,parameter):
        #Write paramter to device to set parameter when locker open
        self.ble.write("short","servo_param",parameter)
        self.ble.write("byte","servo_command",self.open_param_comm)
        
        #Check to parameter wrote by received parameter
        response = self.ble.read("short","status")
        if(response == parameter):
            print("Success to set open paramter. wrote paramter:[%d] response from device:[%d]" % (parameter,response))
        else:
            print("Failed to set parameter %d" % response)
        
        #Move to Idle state
        self.ble.write("byte","servo_command",self.idle_comm)
        
    def setParameterWhenClose(self,parameter):
        #Write paramter to device to set parameter when locker close
        self.ble.write("short","servo_param",parameter)
        self.ble.write("byte","servo_command",self.close_param_comm)

        #Check to parameter wrote by received parameter
        response = self.ble.read("short","status")
        if(response == parameter):
            print("Success to set close paramter. wrote paramter:[%d] response from device:[%d]" % (parameter,response))
        else:
            print("Failed to set parameter %d" % response)

        #Move to Idle state
        self.ble.write("byte","servo_command",self.idle_comm)
    
    def disconnectDevice(self):
        self.ble.disconnect()