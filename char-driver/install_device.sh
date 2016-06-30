echo "Creating device file in your system..."
echo ""

sudo mknod /dev/char_device c 55 1
sudo chmod 777 /dev/char_device

echo "Done."
echo ""
echo "Installing char device driver..."
echo ""
sudo make
sudo insmod char_driver.ko

echo "Done."
echo ""
echo ""
modinfo char_driver.ko

echo "Running tests..."
echo ""
sudo make test

echo "Run the test by typing [./test \"message\"]"
