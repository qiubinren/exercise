#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("usage:./a.out pathname!");
		return -1;
	}	
	char s[100];
	if(argv[1][0]=='/')
	{
		strncpy(s,argv[1],100);
	}
	else
	{
		getcwd(s,100);
		strncat(s,"/",100);
		strncat(s,argv[1],100);
	}
	mkdir(s,0777);	
	return 0;
}
