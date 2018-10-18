from bluepy.btle import *

# MAC adddress of RN4020 is 00:1e:c0:4a:29:6d
# reference http://ianharvey.github.io/bluepy-doc/
# japanese site https://qiita.com/iton/items/a0db46ebbe976494222a


class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self,dev,isNewDev,isNewData):
        if isNewDev:
            print("Discovered device", dev.addr)

        elif isNewData:
            print("Received new data from", dev.addr)

class hoge():
    def __init__(self,MACaddr):
        self.ble = Scanner().withDelegate(ScanDelegate())
        self.device = scanner.scan(10.0)

        for dev in devices:
            print ("Device %s (%s), RSSI=%d dB" % (dev.addr, dev.addrType, dev.rssi))
            for (adtype, desc, value) in dev.getScanData():
                print ("  %s = %s" % (desc, value))


    def scan(self,):
        pass

    def connect(self):
        pass

    def disconnect(self):
        pass
    
    def write(self,uuid):
        pass

    def read(self,uuid):
        pass

    


service_uuid         = "3A41CCA5A1F946909D5E11A946BAFCB4"
characteristic_uuid1 = "1713453B292E4B1C9515F23DDAC2B2B0"
characteristic_uuid2 = "EB57140A35404A6D8C9740D75DF4CBEF"

scaner = Scanner(0)
devices = scaner.scan(3)

for dev in devices:
    print ("Device %s (%s), RSSI=%d dB"%(dev.addr, dev.addrType, dev.rssi))

prphe = Peripheral()
try:
    prphe.connect("00:1e:c0:4a:29:6d",ADDR_TYPE_PUBLIC)
except BTLEException:
    print("error connect")

srv = prphe.getServicesByUUID("00:1e:c0:4a:29:6d")
chara = prphe.getCharacteristics()

for k in chara:
    print(k.uuid)