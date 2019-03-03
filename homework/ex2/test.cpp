#include <iostream>
#include "CLFileControl.h"
#include <stdio.h>

using namespace std;

char File[10]="Head.in",Msg[4096];
CLFileControl A(File);

int main()
{
	A.ReadFile(10);
	A.ReadFile(5);
	A.ReadFile(20);

	printf("Input the massage,end with the EOF.\n");
	fgets(Msg,4096,stdin);
	//gets(Msg);
	A.WriteFile(Msg);
	A.ReadFile(100);

	A.WriteFile(Msg);
	return 0;
}
