#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>

using namespace std;

__thread int x = 5;

void *thread(void *arg)
{
	x++;

	long i = (long)arg;
	if(i == 1)
	{
		sleep(3);
		cout << "thread 1: x = " << x << endl;
	}
	else
	{
		sleep(5);
		cout << "thread 2: x = " << x << endl;
	}
	
	return (void *)0;
}

int main()
{
    pthread_t tid1;
	if(pthread_create(&tid1, NULL, thread, (void *)1) != 0)
	{
	    cout << "pthread_create error" << endl;
		return 0;
	}

	pthread_t tid2;
	if(pthread_create(&tid2, NULL, thread, (void *)2) != 0)
	{
		cout << "pthread_create error" << endl;
		return 0;
	}

	pthread_join(tid1, 0);
	pthread_join(tid2, 0);

	int y = x;
	
	cout << "in main thread, x = " << y << endl;
	
	return 0;
}
