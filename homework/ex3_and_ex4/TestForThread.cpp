#include <iostream>
#include <cstring>
#include <cstdio>
#include "UserThread.h"
#include "MsgQueue.h"
#include "SonThread.h"
#include "MasterThread.h"
#include <unistd.h>

using namespace std;

int main()
{
	UserThread *U=new UserThread;
	U->Run();

	U->Q.info( Msg(ADD_MSG,0,1,2) );
	U->Q.info( Msg(ADD_MSG,1,2,3) );

	sleep(2);
	U->Q.info( Msg(STOP_MSG,0,0,0) );
	
	U->WaitForDeath();

	delete U ;
	return 0;
}
