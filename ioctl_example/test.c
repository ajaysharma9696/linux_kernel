#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "ioctl_cmds.h"

int main(){
    struct mystruct test = {20, "Ajay's ioctl example"};
    int dev = open("/dev/dummy", O_WRONLY);
    if (dev == -1) {
	printf("ioctl example failed to open device\n");
	return -1;
    }
	
    printf("Opening was successful dev %d\n", dev);

    int32_t val = 50;
    ioctl(dev, IO_READ_CMD, &val);
    printf("value read from kernel %d \n", val);

    val = 55;
    ioctl(dev, IO_WRITE_CMD, &val);
    ioctl(dev, IO_READ_CMD, &val);
    printf("Value read from kernel %d \n", val);

    ioctl(dev, IO_GREET_CMD, &test);
    
    close(dev);
    return 0;

}
