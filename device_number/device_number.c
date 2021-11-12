#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>


/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ajay Kumar Sharma");
MODULE_DESCRIPTION("A device number module, registers some callback function");

/**
@brief called when device file is opened
*/

static int driver_open(struct inode *device_file, struct file *instance) {
    printk("device number driver open called \n");
    return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
    printk("device number driver close called \n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close

};


#define MYMAJOR 90

static int __init mymodule_init(void)
{
    int retval;
    printk("Hello from device number module \n");
    
    retval = register_chrdev(MYMAJOR, "device_number", &fops);
    if (retval == 0) {
        printk("device number registered major %d, minor %d \n", MYMAJOR, 0);
    } else if (retval > 0) {
	printk("device number already registered major %d, minor %d", retval>>20, retval&0xfffff); 
    } else {
	printk("device number could not be registered \n");
	return -1;
    }

    return 0;
}



void __exit mymodule_exit(void)
{
    unregister_chrdev(MYMAJOR, "device_number");
    printk("Good bye from device number module \n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
