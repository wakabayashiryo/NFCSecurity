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
    def __init__(self,MACaddr):
        self.error_code = ["DISCONNECTED","COMM_ERROR","INTERNAL_ERROR","GATT_ERROR","MGMT_ERROR"]

        self.mac = MACaddr
        self.ble = Scanner().withDelegate(ScanDelegate())

        self.prphe = Peripheral()

    def scan(self,):
        self.devices = self.ble.scan(timeout=1.0)        

    def Show_detail(self):
        pass

    def connect(self):
        try:
            self.prphe.connect(self.mac,ADDR_TYPE_PUBLIC)
        except BTLEException as BLEexc:
            print("The error cotents is "+self.error_code[BLEexc.code-1])
            print(BLEexc.message)

    def disconnect(self):
        try:
            self.prphe.connect(self.mac,ADDR_TYPE_PUBLIC)
        except BTLEException as BLEexc:
            print("The error cotents is "+self.error_code[BLEexc.code-1])
    
    def write(self,uuid):
        pass

    def read(self,uuid):
        pass


if __name__ == '__main__':    
    service_uuid         = "3A41CCA5-A1F9-4690-9D5E-11A946BAFCB4"
    characteristic_uuid1 = "1713453B-292E-4B1C-9515-F23DDAC2B2B0"
    characteristic_uuid2 = "EB57140A-3540-4A6D-8C97-40D75DF4CBEF"

    ble = BLEcontroller("00:1e:c0:4a:29:6d");
    ble.connect()

    srv = ble.prphe.getServices()
    for s in srv:
        print(s.uuid)

    if [str(srvs) in service_uuid for srvs in srv]:
        print("found service")
    else:
        print()

    chara = ble.prphe.getCharacteristics()

    for k in chara:
        print(k.uuid)