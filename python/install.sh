#!/bin/sh
echo "\033[31m[action]\033[33m >>>> Install necessary packages\033[0m"
sleep 3
sudo apt-get install -y libglib2.0-dev libdbus-1-dev libudev-dev libical-dev libreadline-dev
sudo apt-get install -y bluetooth bluez

echo "\033[31m[action]\033[33m >>>> Install Bluepy library\033[0m"
sleep 3
git clone https://github.com/IanHarvey/bluepy.git
cd bluepy
sudo python3 setup.py install
cd ../
sudo rm -R bluepy/

echo "\n\033[31m[action]\033[33m >>>> Complile source code of bluepy\033[0m"
sleep 3
cd /usr/local/lib/python3.6/dist-packages/bluepy-1.2.0-py3.6.egg/bluepy
sudo make -j

echo "\n\033[31m[action]\033[33m >>>> Check status  bluetooth module and enable it\033[0m"
sleep 3
sudo systemctl status bluetooth
sudo systemctl start bluetooth
