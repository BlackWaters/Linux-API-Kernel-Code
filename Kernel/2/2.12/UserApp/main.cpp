#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <string>

using namespace std;


void *Use(void *arg)
{
	string toSend = "hello driver";
    int ret,fd;
	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return (void*)-1;
	}

	ret = write(fd, toSend.c_str(), toSend.size());	
	if(ret < 0)
	{
		cerr << strerror(errno) << endl;
		close(fd);
		return (void*)-1;	
	}

	close(fd);
    return (void *)0;
}
/*
void createThread()
{
    pthread_t pid[10];
    for (int i=0;i<10;i++) pthread_create(&pid[i],NULL,Use,NULL);
    return ;
}*/

int main()
{
//    createThread();
	int fd = 0;
	int ret;

	string toSend = "hello driver";

	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return -1;
	}

	ret = write(fd, toSend.c_str(), toSend.size());	
	if(ret < 0)
	{
		cerr << strerror(errno) << endl;
		close(fd);
		return -1;	
	}

	close(fd);

	return 0;
}
