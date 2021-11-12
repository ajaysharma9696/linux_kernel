#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int dev = open("/dev/mydevice", O_RDONLY);
    if (dev == -1) {
	printf("Failed to open device device number\n");
	return -1;
    }
	
    printf("Opening was successful\n");
    close(dev);
    return 0;

}
