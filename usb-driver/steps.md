# showing info from usb device

* shows which driver is responsible for dealing with the device

                sudo su
                cat /sys/kernel/debug/usb/devices 

* shows information about usb device

                lsusb -v

# showing kernel log

                tail -f /var/log/kern.log

# inserting the device driver

                sudo make
                sudo insmod usb_driver.ko
                lsmod | grep usb

* note that usb-storage is responsible for the device. So, first we need to remove this module

                sudo modprobe -r usb_storage or
                sudo rmmod usb_storage

# showing info of usb_driver

                modinfo usb_driver.ko

# removing the device driver

                sudo rmmod usb_driver
