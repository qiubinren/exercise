#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int a[10000];
int b[10000]={0};
int fun(const void* a,const void* b)
{
	return (int*)b-(int*)a;
}
int main()
{
	srand(time(NULL));
	int i;
	for(i=0;i<10000;i++)
	{
		a[i]=rand()%10000;
		b[a[i++]]++;
	}
	int sum=0;
	for(i=9999;i>=0;i--)
	{
		if(b[i]>0)
		{
			sum+=b[i];
			if(sum>=10)
			{
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}
