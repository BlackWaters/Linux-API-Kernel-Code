#ifndef Mutex_h
#define Mutex_h

#include <iostream>
#include <cstring>
#include <cstdio>
#include <pthread.h>

using namespace std;

class Mutex
{
	public:
		Mutex() 
		{
			int r=pthread_mutex_init(&Mu,0);
			if (r!=0) printf("Init mutex error.\n");
		}
		~Mutex()
		{
			int r=pthread_mutex_destroy(&Mu);
			if (r!=0) printf("Destroy mutex error.\n");
		}

		int Lock()
		{
			int r=pthread_mutex_lock(&Mu);
			if (r!=0) 
			{
				printf("Lock error.\n");
				return -1;
			}
			return 0;
		}

		int Unlock()
		{
			int r=pthread_mutex_unlock(&Mu);
			if (r!=0)
			{
				printf("Unlock error.\n");
				return -1;
			}
			return 0;
		}

	public:
		pthread_mutex_t Mu;
};

#endif
