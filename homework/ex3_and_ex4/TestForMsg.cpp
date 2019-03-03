#include <iostream>
#include <cstring>
#include <cstdio>
#include "MsgQueue.h"
#include "CLThread.h"
#include <unistd.h>

using namespace std;

class TestThread : public CLThread
{
	public:
		TestThread(){num=0;}
		~TestThread(){}

		virtual int RunThreadFunction()
		{
			while (true)
			{
				num++;
				Msg u=Q.TryGetMsg();
				printf("%d %d %d.\n",u.msg_id,u.op1,u.op2);
				if (num==5) 
				{
					printf("Have recieved 5 Msg.\n");
					return 1;
				}
			}
		}
	public:
		MsgQueue Q;

	private:
		int num;
};


void* Startfunction(void  *a)
{
	sleep(2);
	printf("Hello World %ld \n",(long) a);
	return 0;
}

int main()
{
	MsgQueue Q;
	Msg u(ADD_MSG,1,1,2);
	Q.info(u);

	Msg t=Q.TryGetMsg();
	printf("%d %d %d\n",t.msg_id,t.op1,t.op2);


	TestThread *A=new TestThread;
	A->Run();

	for (int i=1;i<=5;i++) A->Q.info( Msg(ADD_MSG,i,i*2 ,i*2+1) );
	

	//pthread_t p_id;
	//pthread_create(&p_id,NULL,Startfunction,(void *)5);

	sleep(3);
	return 0;
}
