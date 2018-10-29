from bluepy.btle import *
from struct import *

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)
        self.device_count = 0

    def handleDiscovery(self,dev,isNewDev,isNewData):
        if isNewDev:
            self.device_count += 1
            print ("\033[32m%d.Device %s (%s), RSSI=%d dB\033[0m" % (self.device_count,dev.addr, dev.addrType, dev.rssi))
            for (adtype, desc, value) in dev.getScanData():
                print ("  %s = %s" % (desc, value))

        elif isNewData:
            print("\033[31mReceived new data from %s \033[0m"& dev.addr)

class NotifyDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleNotification(self,cHandle,data):
        print("\033[36mHandle %x, Data %d \033[0m" % (cHandle,unpack('<B',data)))

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

    def scan(self,timeout=10.0):
        self.devices = self.scanner.scan(timeout)        
        
    def connect(self,showGATT=False):
        try:
            self.peripheral.connect(self.mac,self.type)
            self.peripheral.setDelegate(NotifyDelegate())
        except BTLEException as BLEexc:
            self.error_message(BLEexc)

        print("\n\033[33mConnected Device %s (%s) \033[0m" % (self.mac,self.type))
        
        if showGATT is True:
            srvs = self.peripheral.getServices()
            print("\n\033[32mThe detail of GATT server connected.")
            for srv in srvs:
                print('\033[33m[Service]\n[UUID]:%s ' % srv.uuid)
                charas = srv.getCharacteristics()
                print("\t\033[34m[Characteristic]") 
                for chara in charas:
                    print('\t[UUID]:%s [Handle]:0x%04X [Property]:%s' % (chara.uuid,chara.getHandle(),chara.propertiesToString()))
                print("\033[0m")
        
        self.checkAllocation()

    def disconnect(self):
        try:
            self.peripheral.disconnect()
        except BTLEException as BLEexc:
            self.error_message(BLEexc)

        print("\n\033[33mDisonnected Device %s (%s) \033[0m" % (self.mac,self.type))
        
    def checkAllocation(self):
        print("\033[4mCheck the specified UUID\033[0m")
        print("\033[32mMatched services\033[33m")
        for key,srv in zip(self.ServiceDict.keys(),self.ServiceDict.values()):
            tmp = self.peripheral.getServiceByUUID(srv)
            print('\t[Key]:%s [UUID]:%s ' % (key,tmp.uuid))

        print("\n\033[32mMatched Characteristics \033[34m")
        for key,chara in zip(self.HandlesDict.keys(),self.CharacteristicDict.values()):
            tmp = self.peripheral.getCharacteristics(uuid=chara)
            self.HandlesDict[key] = tmp[0].getHandle()
            print('\t[Key]:%s [UUID]:%s [Handle]:0x%04X [Property]:%s' % (key,tmp[0].uuid,tmp[0].getHandle(),tmp[0].propertiesToString()))
            
        print("\033[0m")

    def write(self,key,value):
        
        data_type = '>H'
        try:
            self.peripheral.writeCharacteristic(self.HandlesDict[key],pack(data_type,value),withResponse=True)
        except BTLEException as BLEexc:
            self.error_message(BLEexc)
    
    def read(self,key):
        data_type = '>H'
        try:
            return unpack(data_type,self.peripheral.readCharacteristic(self.HandlesDict[key]))[0]
        except BTLEException as BLEexc:
            self.error_message(BLEexc)
        
    def error_message(self,exce):
        error_code = ["disconnected.","common error.","internal error.","GATT error.","managment error."]
        print("\033[31mThe error cotents is "+error_code[exce.code-1])
        print(exce.message + ".\033[0m")


if __name__ == '__main__':
    ble = BLEcontroller("00:1e:c0:4a:29:6d",ADDR_TYPE_PUBLIC)
    
    ble.setService("SmartLoker",'3A41CCA5-A1F9-4690-9D5E-11A946BAFCB4')
    
    ble.setCharacteristic("servo" ,'EB57140A-3540-4A6D-8C97-40D75DF4CBEF')
    ble.setCharacteristic("status",'A57CB712-3FD3-4075-9F92-528225EE04BE')
    
    # ble.scan()
    ble.connect()
    ble.write("servo",100)
    print(ble.read("status"))  

    ble.disconnect()
