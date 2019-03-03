#ifndef USERTHREAD_H
#define USERTHREAD_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include "MsgQueue.h"
#include "MasterThread.h"

using namespace std;

class UserThread : public CLThread
{
        public:
		UserThread()
		{
			Father=new MasterThread;
			Father->Run();
		}
		~UserThread()
		{
			printf("%d\n"  ,Father->GetRest()) ;
			Father->Q.info( Msg(STOP_MSG,0,0,0) );
			Father->WaitForDeath();
			delete Father ;
		}

                virtual int RunThreadFunction()
                {
			while (true)
			{
				Msg u=Q.TryGetMsg();
				if (u.msg_type==ADD_MSG)
				{
					printf("In the user thread.\n");
					Father->Q.info( u );
				}
				if (u.msg_type==STOP_MSG)
					break;
			}
			return 0;

                }
	public:
		MsgQueue Q;

	private:
		MasterThread *Father;
};

#endif 
