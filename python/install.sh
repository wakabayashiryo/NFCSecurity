#!/bin/sh
echo "\033[31m[action]\033[33m >>>> Install necessary packages\033[0m"
sleep 3
sudo apt-get install -y libglib2.0-dev libdbus-1-dev libudev-dev libical-dev libreadline-dev
sudo apt-get install -y bluetooth bluez

echo "\033[31m[action]\033[33m >>>> Install Bluepy library\033[0m"
sleep 3
git clone https://github.com/IanHarvey/bluepy.git
cd bluepy

ans=NULL
while [ "$ans" != "2" ] && [ "$ans" != "3" ]
do
echo "Which version of python will you install bluepy?[2 or 3]"
read ans  
    if test "$ans" = "2" ; then
	echo "install bluepy on python2"
    sudo python setup.py build
    sudo python setup.py install

    elif test "$ans" = "3"; then
	echo "install bluepy on python2"
    sudo python3 setup.py build
    sudo python3 setup.py install

    else
	echo "Sorry, Wrong Word"
    fi
done

cd ../
sudo rm -R bluepy/

echo "\n\033[31m[action]\033[33m >>>> Check status  bluetooth module and enable it\033[0m"
sleep 3
sudo systemctl status bluetooth
sudo systemctl start bluetooth
