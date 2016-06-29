#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define PENDRIVE_VENDOR_ID 0x13fe
#define PENDRIVE_PRODUCT_ID 0x4100

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Igor Ribeiro, Renata Soares and Vitor Barbosa");
MODULE_DESCRIPTION("USB Driver for Fundaments of Operational Systems project");

//probe function
//called on device insertion if and only if no other driver has beat us to the punch
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id){
	printk(KERN_INFO "[*] FSO Pen drive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
	return 0; //return 0 indicates we will manage this device
};

// called when the pen drive is disconnect
static void pen_disconnect(struct usb_interface *interface){
	printk(KERN_INFO "[*] Pen drive removed\n");
};

// usb_device_id
static struct usb_device_id pen_table[] = {
	//0781:5406
	{ USB_DEVICE(PENDRIVE_VENDOR_ID, PENDRIVE_PRODUCT_ID) }, //information is obtained using "lsusb" at the command line
    { USB_DEVICE(0x0930, 0x6544) },
	{} /* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, pen_table);

static struct usb_driver pen_driver = 
{
	.name = "USB-Driver",
	.id_table = pen_table,
	.probe = pen_probe,
	.disconnect = pen_disconnect,
};

static int __init pen_init(void){
	int ret = -1;
	
	printk(KERN_INFO "[*] Constructor of driver");
	printk(KERN_INFO "\tRegistering Driver with Kernel");
	ret = usb_register(&pen_driver);
	printk(KERN_INFO "\nRegistration is complete");

	return ret;
}

static void __exit pen_exit(void){
    printk(KERN_INFO "[*] Destructor of driver");
    usb_deregister(&pen_driver);
    printk(KERN_INFO "\tunregistration complete");
}

module_init(pen_init);
module_exit(pen_exit);
