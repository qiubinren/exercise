#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
int main(int argc,char* argv[])
{
	char command[]="./charreserver";
	FILE* fd=popen(command,"r");
	int size=0;
	char buf[100];
	while(fgets(buf,sizeof(buf),fd)!=NULL)
	{
		int n=strlen(buf);
		if(buf[n-1]=='\n')
			buf[n-1]=0;
		puts(buf);
	}
	return 0;
}
