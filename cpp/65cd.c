#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("usage:./a.out path");
		return -1;
	}
	char s[100];
	if(argv[1][0]!='/'||strcmp(argv[1],"..")==0)
	{
		getcwd(s,100);
		strncat(s,"/",100);
		strncat(s,argv[1],100);
	}
	else
		strncpy(s,argv[1],100);
	chdir(s);
	printf("%s\n",getcwd(NULL,0));
	return 0;
}
