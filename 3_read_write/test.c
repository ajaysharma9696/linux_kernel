#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static char buf[255];
int main(){
    
    int dev = open("/dev/dummydriver", O_RDWR);
    if (dev == -1) {
	printf("Failed to open device device number\n");
	return -1;
    }

	
    printf("Opening was successful dev %d\n", dev);
   
    write(dev, "Hello Kernel", 12);

    read(dev, buf, 12);
    buf[12] = 0;
    printf(" data read from kernel %s \n", buf);
 
    close(dev);
    return 0;

}
