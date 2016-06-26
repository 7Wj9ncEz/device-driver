#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

//probe function
//called on device insertion if and only if no other driver has beat us to the punch
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id){
	printk(KERN_INFO "[*] FSO Pen drive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
	return 0; //return 0 indicates we will manage this device
}

//disconnect
static void pen_disconnect(struct usb_interface *interface){
	printk(KERN_INFO "[*] Pen drive removed\n");
}

//usb_device_id
static struct usb_device_id pen_table[] = {
	//0781:5406
	{USB_DEVICE(0x0781, 0x5406)}, //information is obtained using "]susb" at the command line
	{} /* Terminating entry */
}

MODULE_DEVICE_TABLE (USB, pen_table);

static struct usb_driver pen_driver = 
{
	.name = "USB-Driver",
	.id_table= pen_table,
	.probe = pen_probe,
	.disconnect = pen_disconnet,
};

static int __init pen_init(void){
	int ret=-1;
	
	printk(KERN_INFO "[*]Constructor of driver");
	printk(KERN_INFO "\tRegistering Driver with Kernel");
	ret = usb_register(&pen_driver);
	printk(KERN_INFO "\nRegistration is complet");

	return ret;
}

static void __exit pen_exit(void){
}

module_init(pen_init);
module_exit(pen_exit);
