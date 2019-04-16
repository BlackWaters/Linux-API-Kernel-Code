#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>//mmap head file

int main (void)
{
    int i;
    int fd;
    char *start;
    char *buf = "butterfly!";

//open /dev/mem with read and write mode
    fd = open ("/dev/mem", O_RDWR);
    if (fd < 0)
    {
        printf("cannot open /dev/mem.");
        return 0;
    }

//map physical memory 0-10 bytes 
    start = (char *)mmap(0, 20, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, fd, 0x76857000UL);
    if(start < 0)
    {
        printf("mmap failed.");
        return 0;
    }
//Read old value
//    for (i = 0; i < 10; i++) printf("old mem[%d]:%c/n", i, *(start + i));
    for(int i=0;i<20;i++)    printf("mem : %c\n",*(start+i+0x100) );



    return 0;
}

