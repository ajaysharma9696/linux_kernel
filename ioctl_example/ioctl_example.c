#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include "ioctl_cmds.h"

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ajay Kumar Sharma");
MODULE_DESCRIPTION("A ioctl example module, registers some callback function");

/**
@brief called when device file is opened
*/

static int driver_open(struct inode *device_file, struct file *instance) {
    printk("ioctl example driver open called \n");
    return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
    printk("ioctl example driver close called \n");
    return 0;
}

/* global value to copy from to user space */
int32_t result = 45;

static long int my_ioctl(struct file* instance, unsigned cmd, unsigned long arg) {
    struct mystruct test;
    
    switch(cmd) {
    case IO_READ_CMD:
	if (copy_to_user((int32_t*)arg, &result, sizeof(result))) {
           printk("ioctl example failed to user \n");
 	} else {
 	   printk("ioctl example copied data to user \n");
        }
   	break;
    case IO_WRITE_CMD:
        if (copy_from_user(&result, (int32_t*)arg, sizeof(result))) {
	    printk("ioctl example failed to copy from user \n");
        } else {
	    printk("ioctl example copied %d from user \n", result);
        }
 	break;
    case IO_GREET_CMD:
        if (copy_from_user(&test, (struct my_struct*) arg, sizeof(test))) {
	    printk(" ioctl example failed to copy form user \n");
 	} else {
            printk("copied from user %d  %s \n", test.num, test.name);
	}
    }

    return 0;
}


static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .unlocked_ioctl = my_ioctl

};


#define MYMAJOR 90

static int __init mymodule_init(void)
{
    int retval;
    printk("Hello from ioctl example module \n");
    
    retval = register_chrdev(MYMAJOR, "ioctl_example", &fops);
    if (retval == 0) {
        printk("device number registered major %d, minor %d \n", MYMAJOR, 0);
    } else if (retval > 0) {
	printk("device number already registered major %d, minor %d", retval>>20, retval&0xfffff); 
    } else {
	printk("device number could not be registered %d \n", retval);
	return -1;
    }

    return 0;
}



void __exit mymodule_exit(void)
{
    unregister_chrdev(MYMAJOR, "ioctl_example");
    printk("Good bye from ioctl example  module \n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
