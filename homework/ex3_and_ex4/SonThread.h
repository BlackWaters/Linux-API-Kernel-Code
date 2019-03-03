#ifndef SONTHREAD_H
#define SONTHREAD_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include "MsgQueue.h"
#include "CLThread.h"

using namespace std;

class MasterThread;


class SonThread : public CLThread
{
        public:
                SonThread() {}
		SonThread(MasterThread* f,int Op1,int Op2) ;
                ~SonThread() ;
                virtual int RunThreadFunction() ;
        private:
		int op1,op2;
		MasterThread *Father;

};

#endif
