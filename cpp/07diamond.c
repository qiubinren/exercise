#include <stdio.h>
#include <math.h>
int main(int argc,char* argv[])
{
	int n=10,i,j;
	for(i=0;i<9;i++)
	{
		for(j=abs(5-i-1);j>=0;j--)
			printf(" ");
		for(j=0;j<((2*i+1)/(n-1)==1?2*(n-1)-(2*i+1):2*i+1);j++)
			printf("*");
		printf("\n");
	}
	return 0;
}
