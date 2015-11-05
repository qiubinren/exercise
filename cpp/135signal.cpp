#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
using namespace std;
void handle1(int sig)
{
	cout<<"你杀不掉我！！！"<<endl;
}
void handle2(int sig)
{
	cout<<"你以为换种方法就能杀了我？？！！"<<endl;
}

int main()
{
	signal(SIGINT,handle1);
	signal(SIGQUIT,handle2);
	while(1)
	{
		sleep(10);
	}
	return 0;
}
