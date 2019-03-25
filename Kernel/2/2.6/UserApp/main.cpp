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

void GetFSBase()
{
	int fd = 0;
	int ret;

	string toSend = "hello driver";
	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return;
	}

	ret = write(fd, toSend.c_str(), toSend.size());	
	if(ret < 0)
	{
		cerr << strerror(errno) << endl;
		close(fd);
		return;	
	}

	close(fd);
}

int main()
{
	unsigned long addr = (unsigned long)&x;
	cout << hex << addr << endl;

	GetFSBase();

	return 0;
}
