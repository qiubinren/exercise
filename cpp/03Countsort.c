#include <stdio.h>
#include <stdlib.h>
int count_sort(int a[],int k)
{
	int i;
	int *b=calloc(k+1,sizeof(int));
	for(i=0;i<k;i++)
	{
		b[a[i]]++;
	}
	int z=0;
	for(i=0;i<k+1;i++)
	{
		while(b[i]-->0)
			a[z++]=i;
	}
	return 0;

}
int main()
{
	int a[10]={0,0,1,10,3,10,3,6,5,0};
	count_sort(a,10);
	int i;
	for(i=0;i<10;i++)
	{
		printf("%d\n",a[i]);
	}
	return 0;
}
