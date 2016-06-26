#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

static struct usb_device_id pen_table[]={
	{USB_DEVICE(0x0781, 0x5406)},
	{}
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
	return ret;
}

static void __exit pen_exit(void){
}

module_init(pen_init);
module_exit(pen_exit);
