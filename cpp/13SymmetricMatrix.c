#include <stdio.h>
int main()
{
	int a[4][4]={1,2,3,4,2,1,3,4,3,3,4,1,4,4,1,4};
	int n=4,i,j;
	int flag=1;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(a[i][j]!=a[j][i])
			{
				flag=0;
				break;
			}
	printf("%d\n",flag);
	return 0;
}
