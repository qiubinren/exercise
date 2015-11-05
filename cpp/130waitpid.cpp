#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>

using namespace std;

int main()
{
	pid_t pid[3];
	int status;
	int i;
	for(i=0;i<3;i++)
	{
		pid[i]=fork();
		if(pid[i]<0)
		{
			perror("fork");
			exit(-1);
		}
		else if(pid[i]==0)
		{
			sleep(2);
			exit(i);
		}
	}
	while(waitpid(-1,&status,0)>0)
	{
		if(WIFEXITED(status))
			cout<<WEXITSTATUS(status)<<endl;
		continue;
	}
	return 0;
}
