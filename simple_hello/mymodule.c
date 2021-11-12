#include <linux/module.h>
#include <linux/init.h>


/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ajay Kumar Sharma");
MODULE_DESCRIPTION("A hello world LKM");

static int __init mymodule_init(void)
{
    printk("Hello from aks module \n");
    return 0;
}



void __exit mymodule_exit(void)
{
    printk("Good bye from aks module \n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
