#ifndef Event_h
#define Event_h

#include <iostream>
#include <cstring>
#include <cstdio>
#include <pthread.h>
#include "Mutex.h"

using namespace std;

class Event
{
	public:
		Event()
		{
			int r=pthread_cond_init(&Cd,0);
			if (r!=0) printf("Init condition var error.\n");
		}
		~Event()
		{
			int r=pthread_cond_destroy(&Cd);
			if (r!=0) printf("Destroy error.\n");
		}

		int Wait(Mutex *M)
		{
			int r=pthread_cond_wait(&Cd,&(M->Mu));
			if (r!=0) 
			{
				printf("Wait error.\n");
				return -1;
			}
		}

		int Wakeup()
		{
			int r=pthread_cond_signal(&Cd);
			if (r!=0)
			{
				printf("Wakeup error.\n");
				return -1;
			}
		}


	private:
		pthread_cond_t Cd;

};

#endif
