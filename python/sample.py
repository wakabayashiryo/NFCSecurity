from SmartLocker import *
from time import sleep

if __name__ == '__main__':
    locker = SmartLocker(850,2100)
    try:
        while True:
            locker.operateServo('open')
            print(locker.getServoStatus())
            sleep(1)

            locker.operateServo('close')
            print(locker.getServoStatus())
            sleep(1)

    except KeyboardInterrupt:
        exit()
    
