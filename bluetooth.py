from bluepy.btle import *

# MAC adddress of RN4020 is 00:1e:c0:4a:29:6d
# reference http://ianharvey.github.io/bluepy-doc/
# japanese site https://qiita.com/iton/items/a0db46ebbe976494222a

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