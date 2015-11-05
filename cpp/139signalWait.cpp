#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

using namespace std;
void handle(int sig)
{
	int pid;
	while((pid = waitpid(-1,NULL,0))>0)
	{
		cout<<pid<<endl;	
	}
}
int main()
{
	signal(SIGCHLD,handle);
	for(int i=0;i<10;i++)
	{
		int pid = fork();
		if(pid < 0 )
		{
			perror("fork");
			exit(-1);
		}
		else if(pid == 0)
		{
			sleep(2);
			exit(1);
		}
	}
	int time = 10;
	while(time > 0)
	{
		time = sleep(10);
	}
	return 0;
}
