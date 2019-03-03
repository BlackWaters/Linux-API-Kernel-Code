#include "MasterThread.h"
#include "SonThread.h"

SonThread::SonThread(MasterThread* f,int Op1,int Op2) 
{
	Father=f;
	printf("Create son thread.\n");
	op1=Op1; op2=Op2;
}
SonThread::~SonThread()
{
	Father->GetRest();
}

int SonThread::RunThreadFunction()
{
	printf("Thread_id: %d, result: %d \n",(int) pThread_id,op1+op2);
	Father->Q.info( Msg(DONE_MSG,0,0,0) );
	return 0;
}
