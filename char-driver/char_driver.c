#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUMBER 55
#define MINOR_NUMBER 1

static char message[128] = { 0 };
static short message_position = 0;
static int opened_times = 0;

static int char_open(struct inode *i, struct file *f);
static int char_close(struct inode *i, struct file *f);
static ssize_t char_read(struct file *f, char *buffer, size_t length, loff_t *off);
static ssize_t char_write(struct file *f, const char *buffer, size_t length, loff_t *off);

static struct file_operations fops = {
    .read = char_read,
    .write = char_write,
    .open = char_open,
    .close = char_close,
}

static int __init char_init(void){
	int ret = -1;

    ret = register_chrdev(MAJOR_NUMBER, "char_device", &fops);

    if(ret < 0){
        printk(KERN_INFO "[*] Driver registration failed\n");
    }
    else{
	    printk(KERN_INFO "\t[*] Registering Driver with Kernel");
    }

	return ret;
}

static void __exit char_exit(void){
    unregister_chrdev(MAJOR_NUMBER, "char_device");
}

static int char_open(struct inode *i, struct file *f){

}

static int char_close(struct inode *i, struct file *f){

}

static int char_read(struct file *f, char *buffer, size_t length, loff_t *off){

}

static int char_write(struct file *f, const char *buffer, size_t length, loff_t *off){

}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Igor Ribeiro, Renata Soares and Vitor Barbosa");
MODULE_DESCRIPTION("Char Driver for Fundaments of Operational Systems project");

