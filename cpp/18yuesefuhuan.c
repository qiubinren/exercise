#include <stdio.h>
int main()
{
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	int i=0;
	int m=2;
	int s=0;
	int j=0;
	while(i<9)
	{
		if(a[j]!=0)
		{
			s++;
		}
		if(s==m)
		{
			a[j]=0;
			s=0;
			i++;
			printf("%d\n",j+1);
		}
		j++;
		j=j%10;
	}
	return 0;
}
