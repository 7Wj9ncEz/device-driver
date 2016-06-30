echo "Uninstalling this device"

sudo rm /dev/char_device
sudo rmmod char_driver
make clean

echo "Done."
