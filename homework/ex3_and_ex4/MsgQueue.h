#ifndef MsgQueue_h
#define MsgQueue_h

#include <iostream>
#include <cstring>
#include <cstdio>
#include "Mutex.h"
#include "Event.h"
#define maxq 8000
#define ADD_MSG 0
#define DONE_MSG 1
#define STOP_MSG 2

using namespace std;

struct Msg
{
	int op1,op2,msg_id,msg_type;
	Msg()
	{
		op1=op2=msg_id=msg_type=0;
	}
	Msg(int Type,int Id,int Op1,int Op2)
	{
		msg_type=Type;
		msg_id=Id;
		op1=Op1;
		op2=Op2;
	}
};

class MsgQueue
{
	public:
		MsgQueue()
		{
			front=0; tail=0; num=0;
			memset(Msgq,-1,sizeof(Msgq));
		}
		~MsgQueue() {}

		Msg info(Msg m)
		{
			//lock
			bool flag=0;
			L.Lock();

			num++;
			Push(m);
			if (num==1) flag=1;
			L.Unlock();

			if (flag) E.Wakeup();
		}

		Msg TryGetMsg()
		{
			//Msg Suspend_msg(SUSPEND_MSG,0,0);

			//if (num==0) return Suspend_msg;
			L.Lock();

			if (num==0) E.Wait(&L);
			num--;
			Msg ret=Pop();
			L.Unlock();
			return ret;
		}


	private:
		void Push(Msg m)
		{
			Msgq[tail]=m;
			tail=(tail+1)%maxq;  //loop queue
		}

		Msg Pop()
		{
			Msg ret=Msgq[front];
			front=(front+1)%maxq; //loop queue
			return ret;
		}

		int front,tail,num;
		Msg Msgq[maxq];
		Mutex L;
		Event E;
};

#endif
