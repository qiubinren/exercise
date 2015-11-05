#include <stdio.h>
int main()
{
	int a[4][2]={1,2,3,4,1,2,3,4};
	int b[2][4]={1,1,1,1,1,1,1,1};
	int c[4][4]={0};
	int i,j,k;
	for(k=0;k<4;k++)
		for(i=0;i<2;i++)
		{
			for(j=0;j<4;j++)
			{
				c[j][k]+=a[j][i]*b[i][j];
			}
		}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			printf("%d ",c[i][j]);
		printf("\n");
	}
	return 0;
}
