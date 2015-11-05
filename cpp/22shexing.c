#include <stdio.h>
int main()
{
	int i=0,j=0;
	int n=3,m=3;	
	int a[3][3];
	int k=0;
	while(j<3)
	{
		if(j%2==0)
			a[j][i++]=++k;
		else if(j%2==1)
			a[j][--i]=++k;
		if(i%3==0)
			j++;
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
}
