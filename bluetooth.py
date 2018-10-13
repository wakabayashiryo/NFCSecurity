from bluepy.btle import *

# MAC adddress of RN4020 is 00:1e:c0:4a:29:6d
# reference http://ianharvey.github.io/bluepy-doc/
# japanese site https://qiita.com/iton/items/a0db46ebbe976494222a

service_uuid         = "3A41CCA5A1F946909D5E11A946BAFCB4"
characteristic_uuid1 = "1713453B292E4B1C9515F23DDAC2B2B0"
characteristic_uuid2 = "EB57140A35404A6D8C9740D75DF4CBEF"

scaner = Scanner(0)
devices = scaner.scan(3)

for dev in devices:
    print ("Device %s (%s), RSSI=%d dB"%(dev.addr, dev.addrType, dev.rssi))

prphe = Peripheral()
prphe.connect("00:1e:c0:4a:29:6d","public")
srv = prphe.getServices()
chara = prphe.getCharacteristics()

for k in chara:
    print(k.uuid)