raspberry pi ble setting

## BLE specifications

- ### central
    BLE4.2 in Raspberry Pi 3B+ or Zero W
- ### peripheral
    microchip company RN4020
	## 注意:一度ペアリングしてしまうとボンディングした相手しかアドバタイズしないため、他のデバイスでスキャンできなくなるので注意 (No Direct Advertisementをセットして不特定多数にアドバタイズしている）

RN4020 configration    
|commad|   contents    |parameter|
|:----:|:-------------:|:--:|
|SB,4|UART baudrate|115200bps|
|SR,24000000|support fnctions|peripheral|
|||auto advertisement|
|||No Direct Advertisement|
|SS,80040001|support fnctions|Device Information|
|||TX Power|
|||Private service|

|   contents    |uuid|property|bits|use|
|:-------------:|:--:|:-------|:---:|:----:|
|service        | 3A41CCA5A1F946909D5E11A946BAFCB4 |    |     ||
|charactaristic1| 1713453B292E4B1C9515F23DDAC2B2B0 |reading |8| operating servo|
|charactaristic2| EB57140A35404A6D8C9740D75DF4CBEF |writing |8| magnetic sensor|
 


1.confirm depended packages 
> sudo apt-get install -y libglib2.0-dev libdbus-1-dev libudev-dev libical-dev libreadline-dev
   
2. confirm libaray installed 
> sudo apt-get install bluetooth bluez

3. cnfirme bleutooth device behavier    
> sudo hcitool lescan   
if display "Could not open device: No such device",
check deamon service and start service.
> sudo systemctl status bluetooth   
> sudo systemvtl start bluetooth

4. install bluepy
> git clone https://github.com/IanHarvey/bluepy.git   
> sudo pip install bluepy


topic   
	serach BLE device and found its MAC address   
	
	> sudo hcitool lescan   

	or   

	> sudo bluetoothctl   
	> scan on   