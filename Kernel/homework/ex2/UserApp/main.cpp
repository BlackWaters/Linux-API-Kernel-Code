#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <pthread.h>
#define Thread_num 102

using namespace std;

void* UesIO(void *arg)
{
    unsigned int ret=*(int *)arg;
    //if (ret!=0) sleep( rand()%5 +1);
    if (ret==101) sleep(1); 
    int fd=0;
	if ((fd = open("/dev/msg_printer", O_RDWR)) < 0)
    {
        printf("The %dth pthread down.\n",ret);
        cerr << strerror(errno) << endl;	
        return (void*) -1;
    }
    if (ioctl(fd, ret ,1)<0)
    {
        printf("The %dth pthread down.\n",ret);
        cerr << strerror(errno) <<endl;
        return (void*) -1;
    }
    return (void*) 0;
    
}
int a[Thread_num];
pthread_t pid[Thread_num];

void creatThread()
{
    for (int i=0;i<Thread_num;i++) a[i]=i;
//    printf("%x\n",&pid[2]);
 //   system("pause");
    int ret=0,cnt=0;
    for (int i=0;i<Thread_num;i++) 
    {
        //printf("%x %d\n",&pid[i],a[i]);
        ret=0;
        ret=pthread_create(&pid[i],NULL,UesIO,(void *)&a[i]);
        if (ret==0) cnt++;
    }
    printf("The number of thread: %d\n",cnt);
}


int main()
{
    creatThread();
    sleep(4);
    /*
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

    ret=ioctl(fd,1,2);
    printf("%d\n",ret);
	close(fd);
    */


	return 0;
}
