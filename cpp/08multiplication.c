#include <stdio.h>
int main(int argc,char* argv[])
{
	int n=10,i,j;
	for(i=1;i<10;i++)
	{
		for(j=1;j<=i;j++)
			printf("%d*%d=%d ",i,j,i*j);
		printf("\n");
	}
	return 0;
}
