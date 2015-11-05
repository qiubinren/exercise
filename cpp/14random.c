#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int j,b,x;
	int a[10]={0},i;
	srand((unsigned)time(NULL));
	for(i=0;i<10;i++)
		a[i]=rand();
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
	for(i=0;i<10;i++)
	{
		b=i;
		for(j=i+1;j<10;j++)
		{
			if(a[b]>a[j])
				b=j;
		}
		if(b!=i)
		{
			x=a[b];
			a[b]=a[i];
			a[i]=x;
		}	
	}
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
