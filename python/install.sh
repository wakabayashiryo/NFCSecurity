#!/bin/sh
echo "\033[31m[action]\033[33m >>>> Install necessary packages\033[0m"
sleep 3
sudo apt-get install -y libglib2.0-dev libdbus-1-dev libudev-dev libical-dev libreadline-dev
sudo apt-get install -y bluetooth bluez

echo "\n\033[31m[action]\033[33m >>>> Complile source code of bluepy\033[0m"
sleep 3
cd /usr/local/lib/python3.5/dist-packages/bluepy
sudo make

echo "\n\033[31m[action]\033[33m >>>> Check status  bluetooth module and enable it\033[0m"
sleep 3
sudo systemctl status bluetooth
sudo systemctl start bluetooth
