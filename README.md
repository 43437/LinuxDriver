# LinuxDriver
this is a demo for linux driver

这是一个linux驱动的简单例程

add driver: 

sudo insmod globalvar.ko
cat /pro/devices
sudo mknod /dev/globalvar1 c 257 0

remove driver: 

sudo rmmod globalvar
sudo rm /dev/globalvar1
