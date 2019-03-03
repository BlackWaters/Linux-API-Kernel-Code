#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	int fd=open("a.in",O_RDWR | O_APPEND);
	if (fd==-1) 
	{
		printf("open error!\n");
		return 0;
	}
	system("cat a.in");
	puts("");
	int pos=lseek(fd,0,SEEK_CUR);
	printf("Position now : %d\n",pos); // My pos show 0 here

	char *buf=(char *)malloc(sizeof(char)*5);
	if (read(fd,buf,5)==-1)
	{
		printf("read error.\n");
		return 0;
	}
	printf("buffer : %s\n",buf);

	
	int ret=lseek(fd,0,SEEK_SET);
	if (ret==-1)
	{
		printf("lseek error.\n");
		return 0;
	}

	if (write(fd,buf,5)==-1)
	{
		printf("write error.\n");
		printf("%s\n",strerror(errno));
		return 0;
	}
	system("cat a.in");
	puts("");
	delete []buf;
	return 0;
}
