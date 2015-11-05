#include <stdio.h>
int main()
{
	int x=0,y=0,k=0;
	int a[3][3];
	int n=3,start=0,end=3;
	int i,j;
	while(n>0)
	{
		for(i=start;i<end-1;i++)
			a[x][y++]=++k;
		for(i=start;i<end-1;i++)
			a[x++][y]=++k;
		for(i=start;i<end-1;i++)
			a[x][y--]=++k;
		for(i=start;i<end-1;i++)
			a[x--][y]=++k;
		if(start==end-1)
			a[x][y]=++k;
		start++,end--,x++,y++;
		n-=2;
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
}
