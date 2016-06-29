# Create device file using `mknod path type major minor`

         mknod /dev/char_device c 55 1

# showing kernel log

                tail -f /var/log/kern.log

# inserting the device driver

         sudo make
         sudo insmod char_driver.ko

# Testing the driver

         make test
         ./prog "message"
