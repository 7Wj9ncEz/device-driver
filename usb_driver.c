#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define PENDRIVE_VENDOR_ID 0x13fe
#define PENDRIVE_PRODUCT_ID 0x4100

#define MIN(a,b) (((a) <= (b))) ? (a) : (b)

// info extracted from /sys/kernel/debug/usb/devices
#define BULK_EP_OUT 0x02 
#define BULK_EP_IN 0x81
#define MAX_PKT_SIZE 521


static struct usb_device *device;
static struct usb_class_driver class;
static unsigned char bulk_buf[MAX_PKT_SIZE];

static int pen_open(struct inode *i, struct file *f){
    return 0;
}

static int pen_close(struct inode *i, struct file *f){
    return 0;
}

static ssize_t pen_read(struct file *f, char __user *buf, size_t cnt, loff_t *off){
    int retval;
    int read_cnt;

    retval = usb_bulk_msg(device, usb_rcvbulkpipe(device, BULK_EP_IN), bulk_buf, MAX_PKT_SIZE, &read_cnt, 5000);

    // zero if success
    if(retval){
        printk(KERN_ERR "[*] Bulk message returned %d\n", retval);
    }

    if(copy_to_user(buf, bulk_buf, MIN(cnt, read_cnt))){
        return -EFAULT; 
    }

    return MIN(cnt, read_cnt);
}

static ssize_t pen_write(struct file *f, const char __user *buf, size_t cnt, loff_t *off){
    int retval;
    int wrote_cnt = MIN(cnt, MAX_PKT_SIZE);

    if(copy_from_user(bulk_buf, buf, MIN(cnt, MAX_PKT_SIZE))){
        return -EFAULT;
    }

    retval = usb_bulk_msg(device, usb_sndbulkpipe(device, BULK_EP_OUT), bulk_buf, MIN(cnt, MAX_PKT_SIZE), &wrote_cnt, 5000);

    if(retval){
        printk(KERN_ERR "[*] Bulk message returned %d\n", retval);
        return retval;
    }

    return wrote_cnt;
}

static struct file_operations fops = {
    .open = pen_open,
    .release = pen_close,
    .read = pen_read,
    .write = pen_write,
};

//probe function
//called on device insertion if and only if no other driver has beat us to the punch
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id){
    int retval;

	printk(KERN_INFO "[*] FSO Pen drive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);

    device = interface_to_usbdev(interface);

    class.name = "usb/pen%d";
    class.fops = &fops; // struct defined above

    retval = usb_register_dev(interface, &class);
    if(retval < 0){
        printk(KERN_ERR "[*] Not able to get a minor for this device.");
    }
    else{
        printk(KERN_INFO "Minor obtained: %d\n", interface->minor);
    }

    return retval;
};

// called when the pen drive is disconnect
static void pen_disconnect(struct usb_interface *interface){
    usb_deregister_dev(interface, &class);

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

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Igor Ribeiro, Renata Soares and Vitor Barbosa");
MODULE_DESCRIPTION("USB Driver for Fundaments of Operational Systems project");

