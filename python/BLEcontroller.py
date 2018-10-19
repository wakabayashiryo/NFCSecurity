from bluepy.btle import *

# MAC adddress of RN4020 is 00:1e:c0:4a:29:6d

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self,dev,isNewDev,isNewData):
        if isNewDev:
            print ("Device %s (%s), RSSI=%d dB" % (dev.addr, dev.addrType, dev.rssi))
            for (adtype, desc, value) in dev.getScanData():
                print ("  %s = %s" % (desc, value))

        elif isNewData:
            print("Received new data from %s "& dev.addr)

class BLEcontroller:
    def __init__(self,MACaddr,TYPEaddr):
        self.mac = MACaddr
        self.type = TYPEaddr

        self.SeriviceList = {}
        self.CharacteristicList = {}

        self.serach = Scanner().withDelegate(ScanDelegate())
        self.peripheral = Peripheral()

    def setService(self,key,uuid):
        if uuid.isupper():
            self.SeriviceList[key] = uuid.lower()
        else:
            self.SeriviceList[key] = uuid
            
    def setCharacteristic(self,key,uuid):
        if uuid.isupper():
            self.CharacteristicList[key] = uuid.lower()
        else:
            self.CharacteristicList[key] = uuid

    def scan(self,timeout=3.0,show=False):
        self.devices = self.serach.scan(timeout)        
        
    def connect(self):
        try:
            self.peripheral.connect(self.mac,self.type)
        except BTLEException as BLEexc:
            self.error_message(BLEexc)

        srvs = self.peripheral.getServices()
        charas = self.peripheral.getCharacteristics()

        # if all([str(srv.uuid) in self.SeriviceList.values() for srv in srvs]):
        #     print("found service")
        # else:
        #     raise BTLEException(BTLEException.GATT_ERROR,"The UUID registered do not inclued")
        matchNum = 0
        for chara in charas:
            if chara.uuid in self.CharacteristicList.values():
                print(chara.uuid)
                matchNum += 1
        if matchNum is len(self.CharacteristicList):
            raise BTLEException(BTLEException.GATT_ERROR,"The UUID registered do not inclued")

    def disconnect(self):
        try:
            self.peripheral.connect(self.mac,self.type)
        except BTLEException as BLEexc:
            self.error_message(BLEexc)

    def write(self,key,value):
        self.peripheral.writeCharacteristic(self.CharacteristicList[key],value)

    def read(self,key):
        return self.peripheral.readCharacteristic(self.CharacteristicList[key])

    def error_message(self,exce):
        error_code = ["DISCONNECTED","COMM_ERROR","INTERNAL_ERROR","GATT_ERROR","MGMT_ERROR"]
        print("\033[31mThe error cotents is "+error_code[exce.code-1])
        print(exce.message + "\033[0m")


if __name__ == '__main__':    
    service_uuid         = '3A41CCA5-A1F9-4690-9D5E-11A946BAFCB4'
    characteristic_uuid1 = '1713453B-292E-4B1C-9515-F23DDAC2B2B0'
    characteristic_uuid2 = 'EB57140A-3540-4A6D-8C97-40D75DF4CBEF'

    ble = BLEcontroller("00:1e:c0:4a:29:6d",ADDR_TYPE_PUBLIC);
    
    ble.setService("1",service_uuid)
    
    ble.setCharacteristic("1",characteristic_uuid1)
    ble.setCharacteristic("2",characteristic_uuid2)
    
    # ble.scan()

    ble.connect()
