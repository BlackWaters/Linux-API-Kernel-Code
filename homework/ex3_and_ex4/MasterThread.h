#ifndef MASTERTHREAD_H
#define MASTERTHREAD_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include "CLThread.h"
#include "MsgQueue.h"
#include "SonThread.h"

using namespace std;

class MasterThread : public CLThread
{
        public:
                MasterThread() 
		{
			rest=20;
		}
                ~MasterThread() {}

		int GetRest()
		{
			return rest;
		}
                virtual int RunThreadFunction()
                {
                        while (true)
                        {
                                Msg u=Q.TryGetMsg();
				printf("In the father thread.\n");
                                if (u.msg_type==ADD_MSG)
                                {
					L.Lock();
					if (rest>=1)
					{
						rest--;
						SonThread *S=new SonThread(this,u.op1,u.op2);
						S->Run();

						S->Detach();
					}
					L.Unlock();
                                }
				if (u.msg_type==DONE_MSG)
				{
					int p=u.msg_id;
					L.Lock();
					
					rest++;

					L.Unlock();
				}
				if (u.msg_type==STOP_MSG) break ;
                        }

                }
	public:
                MsgQueue Q;
        private:
		int rest;
		Mutex L;
		Event E;
};


#endif
