#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int  fd;

    fd = open("serial.logno", O_CREAT | O_RDWR, 0644);
    if(fd == -1)
    {
        printf("open file fail\n");
        return -1;
    }

    char serno[7] = {'\0'};

    int n = read(fd, serno, 6);
    int count = 0;

    if(n > 0)
    {
        printf("serno: %s\n", serno);
        count = atoi(serno);
    }
    else
    {
        count = 1;
    }

    memset(serno, 0, sizeof(serno));
    count = count + 1;
    sprintf(serno, "%06d", count);

    lseek(fd, SEEK_SET, 0);

    write(fd, serno, 6);

    close(fd);

    return 0;
}
