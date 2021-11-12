#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>


/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ajay Kumar Sharma");
MODULE_DESCRIPTION("Module to auto generate device file and show copy to user space / from user space");

static char buffer[255];
static int buffer_tail;

/* Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "dummydriver"
#define DRIVER_CLASS "mymoduleclass"

/**
@ brief copy data to user from kernel 
*/

static ssize_t driver_read(struct file* fp, char* user_buf, size_t count, loff_t *offset) {
    printk("read write module read function invoked \n");
    int to_copy, delta, not_copied;
    /* Get the amount of data to copy */
    to_copy = min(count, buffer_tail);
    /* Copy data to user */
    not_copied = copy_to_user(user_buf, buffer, to_copy);
    /* Calculate delta */
    delta = to_copy - not_copied;
    
    return delta;
}

static ssize_t driver_write(struct file* fp, const char* user_buf, size_t count, loff_t *offset) {
    printk("read write module write function invoked \n");
    int to_copy, delta, not_copied;
   
    /* Get the amount of data to copy */
    to_copy = min(count, sizeof(buffer));
    /* Copy data from user */
    not_copied = copy_from_user(buffer, user_buf, to_copy);
    
    delta = to_copy - not_copied;
    buffer_tail = delta;

    return delta;
}
/**
@brief called when device file is opened
*/

static int driver_open(struct inode *device_file, struct file *instance) {
    printk("read write driver open called \n");
    return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
    printk("read write driver close called \n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .read = driver_read,
    .write = driver_write
};



static int __init mymodule_init(void)
{
    int retval;
    printk("Hello from read write number module \n");
    
    /* Allocate a device number */
    if (alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0){
        printk("Device could not be allocated \n");
	return -1;
    }

    printk("read write - device number Major %d Minor %d was registered", my_device_nr >> 20, my_device_nr & 0xfffff);

    /* create device class */
    if ((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
	printk("Device class could not be created \n");
	goto ClassError;
    }
    
    /* create a device file */
    if (device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL){
        printk("Cannot create device file \n");
	goto FileError;
    }

    /* Initialize device file */
    cdev_init(&my_device, &fops);
    
    /* Registering device to kernel */
    if (cdev_add(&my_device, my_device_nr, 1) == -1) {
        printk("Registering of device to kernel failed \n");
        goto AddError;
    }

    return 0;

AddError:
    device_destroy(my_class, my_device_nr);
FileError:
    class_destroy(my_class);

ClassError:
    unregister_chrdev(my_device_nr, DRIVER_NAME);
    return -1;
}



void __exit mymodule_exit(void)
{
    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev(my_device_nr, DRIVER_NAME);
    printk("Good bye from read write module \n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
