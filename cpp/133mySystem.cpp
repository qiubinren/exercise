#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main()
{
	pid_t pid = vfork();
	if(pid < 0)
	{
		perror("vfork");
		exit(-1);
	}
	else if(pid == 0)
	{
		execlp("ls","ls","-l",NULL);
		exit(1);
	}
	wait(NULL);
	return 0;
}
