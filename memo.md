raspberry pi ble setting

- ## BLE specifications

- ### central
    BLE4.2 in Raspberry Pi 3B+ or Zero W
- ### peripheral
    microchip company RN4020
	## 注意:一度ペアリングしてしまうとボンディングした相手しかアドバタイズしないため、他のデバイスでスキャンできなくなるので注意 (No Direct Advertisementをセットして不特定多数にアドバタイズしている）

- ## RN4020 configration    

	|commad|   contents    |parameter|   
	|:----:|:-------------:|:--:|   
	|SB,4|UART baudrate|115200bps|    
	|SR,24000000|support fnctions|peripheral|
	|||auto advertisement|
	|||No Direct Advertisement|
	|SS,80040001|support fnctions|Device Information|
	|||TX Power|
	|||Private service|


	|   contents    |uuid|property|bits|use|handle|
	|:-------------:|:--:|:-------|:---:|:----:|:---|
	|service        | 3A41CCA5A1F946909D5E11A946BAFCB4 |    |     |||
	|charactaristic1| 1713453B292E4B1C9515F23DDAC2B2B0 |reading |8| operating servo| 0x001B| 
	|charactaristic2| EB57140A35404A6D8C9740D75DF4CBEF |writing |8| magnetic sensor| 0x001D| 


	1.confirm depended packages 
	
	> sudo apt-get install -y libglib2.0-dev libdbus-1-dev libudev-dev libical-dev libreadline-dev

	2. confirm libaray installed 
	
	> sudo apt-get install bluetooth bluez

	3. confirm bleutooth device behavier    
	
	> sudo hcitool lescan   
	
	if display "Could not open device: No such device",
	check deamon service and start service.
	
	> sudo systemctl status bluetooth  
	> sudo systemctl start bluetooth    

	4. install bluepy
	
	> git clone https://github.com/IanHarvey/bluepy.git   
	> sudo pip install bluepy

	topic:Other way to serach BLE device and confirm its MAC address
	> sudo bluetoothctl   
	> \#scan on

### **When executing the command, the following message is displayed.**
> $FileNotFoundError: [Errno 2] No such file or directory: '/usr/local/lib/python3.5/dist-packages/bluepy-1.2.0-py3.5.egg/bluepy/bluepy-helper'

Excute the command at */usr/local/lib/python3.5/dist-packages/bluepy-1.2.0-py3.5.egg/bluepy*
> sudo make

        # switch servo command
        # 0: close
        # 1: open
        # 2: set open parameter
        # 3: set close parameter
        
        # setting sequense
        # 1. write open parameters
        # 2. write No.2 to switch servo characteristic to store open parameter in device
        # 3. compare whether the transmitted parameter is the same as the value received from status characteristic
        # 4. write close parameters
        # 5. write No.3 to switch servo characteristic to store close parameter in device
        # 6. compare whether the transmitted parameter is the same as the value received from status characteristic
        # 7. write No.0 to switch servo characteristic
        
