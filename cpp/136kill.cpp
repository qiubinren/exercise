#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
using namespace std;

void handle(int sig)
{
	cout<<"你杀不掉我！！！"<<endl;
}
int main()
{
	signal(SIGINT, handle);
	while(1)
	{
		sleep(1);
		kill(getpid(),SIGINT);
	}
}
