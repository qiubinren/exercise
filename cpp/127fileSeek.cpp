#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
	int fd = open("test",O_RDONLY);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}
	char d[3];
	read(fd,d,sizeof(d)-1);
	d[2]=0;
	cout<<d<<endl;
	int pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(-1);
	}
	else if(pid==0)
	{
		read(fd,d,sizeof(d)-1);
		d[2]=0;
		cout<<d<<endl;
	}
	else
		sleep(2);
	return 0;
}
