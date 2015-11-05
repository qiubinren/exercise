#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>

using namespace std;

int main(int argc,char *argv[])
{
	const char *path;
	if(argc<2)
	{
		path = ".";
	}
	else
		path = argv[1];
	pid_t pid = fork();
	if(pid<0)
	{
		perror("fork");
		exit(-1);
	}
	if(pid ==0)
	{
		execlp("ls","ls","-l", path, NULL);
	}
	else
		wait(NULL);
	return 0;
}
