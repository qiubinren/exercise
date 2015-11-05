#include <stdio.h>
int main(int argc,char* argv[])
{
	int n=10,i,j;
	for(i=0;i<n;i++)
	{
		for(j=n-i;j>0;j--)
			printf(" ");
		for(j=1;j<2*(i+1);j++)
			printf("*");
		printf("\n");
	}
	return 0;
}
