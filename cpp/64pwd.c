#include <unistd.h>
#include <stdio.h>
int main(int argc,char** argv)
{
	//char buf[100];
	//getcwd(buf,100);
	//printf("%s\n",buf);
	printf("%s\n",getcwd(NULL,0));
	return 0;
}
