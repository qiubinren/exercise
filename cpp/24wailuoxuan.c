#include <stdio.h>
int main()
{
	int a[3][3];
	int i=0,j;
	int x,y;
	x=y=(3-1)/2;
	a[x][y]=1;
	int len=1;
	int count=0;
	int k=2;
	int dir=1;
	while(k<=9)
	{
		for(i=0;k<=9&&i<len;i++)
		{
			switch(dir)
			{
				case 0:
					--x;	break;
				case 1:
					++y;	break;
				case 2:
					++x;	break;
				case 3:
					--y;	break;
			}
			a[x][y]=k++;
		}
		count++;
		if(count==2)
		{
			count=0;
			len++;
		}
		dir=(dir+1)%4;
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
}
