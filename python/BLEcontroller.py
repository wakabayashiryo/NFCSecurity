from bluepy.btle import *
from struct import *

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self,dev,isNewDev,isNewData):
        if isNewDev:
            print ("\033[32mDevice %s (%s), RSSI=%d dB\033[0m" % (dev.addr, dev.addrType, dev.rssi))
            for (adtype, desc, value) in dev.getScanData():
                print ("  %s = %s" % (desc, value))

        elif isNewData:
            print("\033[31mReceived new data from %s \033[0m"& dev.addr)

class BLEcontroller:
    def __init__(self,MACaddr,TYPEaddr):
        self.mac  = MACaddr
        self.type = TYPEaddr

        self.ServiceDict = {}
        self.HandlesDict = {}
        self.CharacteristicDict = {}

        self.scanner    = Scanner().withDelegate(ScanDelegate())
        self.peripheral = Peripheral()

    def setService(self,key,uuid):
        self.ServiceDict[key] = UUID(uuid)

    def setCharacteristic(self,key,uuid):
        self.HandlesDict[key] = None
        self.CharacteristicDict[key] = UUID(uuid)

    def scan(self,timeout=3.0):
        self.devices = self.scanner.scan(timeout)        
        
    def connect(self):
        try:
            self.peripheral.connect(self.mac,self.type)
        except BTLEException as BLEexc:
            self.error_message(BLEexc)

        print("\n\033[33mMatched service list\033[32m")
        for key,srv in zip(self.ServiceDict.keys(),self.ServiceDict.values()):
            tmp = self.peripheral.getServiceByUUID(srv)
            print('[Key]:%s [UUID]:%s ' % (key,tmp.uuid))

        print("\n\033[33mMatched Characteristic list\033[32m")
        for key,chara in zip(self.HandlesDict.keys(),self.CharacteristicDict.values()):
            tmp = self.peripheral.getCharacteristics(uuid=chara)
            self.HandlesDict[key] = tmp[0].getHandle()
            print('[Key]:%s [UUID]:%s [Handle]:0x00%X ' % (key,tmp[0].uuid,tmp[0].getHandle()))
            
        print("\033[0m")

    def disconnect(self):
        try:
            self.peripheral.connect(self.mac,self.type)
        except BTLEException as BLEexc:
            self.error_message(BLEexc)

    def write(self,key,value):
        try:
            self.peripheral.writeCharacteristic(self.HandlesDict[key],value,withResponse=True)
        except BTLEException as BLEexc:
            self.error_message(BLEexc)
    
    def read(self,key):
        try:
            return self.peripheral.readCharacteristic(self.HandlesDict[key])
        except BTLEException as BLEexc:
            self.error_message(BLEexc)
        
    def error_message(self,exce):
        error_code = ["disconnected.","common error.","internal error.","GATT error.","managment error."]
        print("\033[31mThe error cotents is "+error_code[exce.code-1])
        print(exce.message + ".\033[0m")


if __name__ == '__main__':
    ble = BLEcontroller("00:1e:c0:4a:29:6d",ADDR_TYPE_PUBLIC)
    # ble = BLEcontroller("00:1e:c0:55:2f:20",ADDR_TYPE_PUBLIC)
    
    ble.setService("SmartLoker",'3A41CCA5-A1F9-4690-9D5E-11A946BAFCB4')
    
    ble.setCharacteristic("sensor",'1713453B-292E-4B1C-9515-F23DDAC2B2B0')
    ble.setCharacteristic("servo",'EB57140A-3540-4A6D-8C97-40D75DF4CBEF')
    
    # ble.scan(10)
    ble.connect()

    ble.write("servo",pack('B',11))
    print(unpack('B',ble.read("sensor")))    
