#ifndef _IOCTL_CMDS_H
#define _IOCTL_CMDS_H

struct mystruct {
    int num;
    char name[256];
};

#define IO_READ_CMD         _IOR('a', 'a', int32_t *)
#define IO_WRITE_CMD        _IOW('a', 'b', int32_t *)
#define IO_GREET_CMD        _IOW('a', 'c', struct mystruct *)



#endif
