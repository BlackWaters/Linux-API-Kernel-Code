#ifndef CLThread_h
#define CLThread_h

#include <iostream>
#include <cstring>
#include <cstdio>
#include <pthread.h>
#include "MsgQueue.h"
#define maxpoor 8000

using namespace std;

class CLThread
{
	public:
		CLThread(){}
		~CLThread(){}
		int Run()
		{
			int r=pthread_create(&pThread_id,0,StartFunction,this);
			if (r!=0)
			{
				printf("Can't run thread.\n");
				return -1;
			}
			return 0;
		}
		int WaitForDeath()
		{
			int r=pthread_join(pThread_id,0);
			if (r!=0)
			{
				printf("pthread_join error.\n");
				return -1;
			}
			return 0;
		}

		int Detach()
		{
			int r=pthread_detach(pThread_id);
			if (r!=0) 
			{
				printf("Detach failed.\n"); 
				return -1;
			}
			return 0;
		}


	private:
		static void* StartFunction(void *pThis)
		{
			CLThread *pThreadthis=(CLThread *) pThis;
			int r=pThreadthis->RunThreadFunction();
			if (r==-1)
			{
				printf("Can't run thread function.");
				;	
			}
			return 0;

		}

	protected:
		pthread_t pThread_id;
		virtual int RunThreadFunction() {};
			
};

#endif

