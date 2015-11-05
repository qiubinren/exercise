#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>

using namespace std;

int main()
{
	int pid;
	if(pid = fork())
		exit(0);
	setsid();
	if(pid = fork())
		exit(0);
	for(int i=0;i<3;i++)
		close(i);
	chdir("/");
	umask(9);
	signal(SIGCHLD,SIG_IGN);
	while(1)
	{
		sleep(10);
	}
	return 0;
}
