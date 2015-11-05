#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int quicksort(int a[],int left,int right)
{
	if(left<right)
		{
			int i=left,j=right;
			int x=a[i];
			while(i<j)
			{
				while(i<j&&a[j]>x)
					j--;
				if(i<j)
					a[i++]=a[j];
				while(i<j&&a[i]<x)
					i++;
				if(i<j)
					a[j--]=a[i];
			}
			a[i]=x;
			quicksort(a,left,i-1);
			quicksort(a,i+1,right);
		}
	return 0;
}
int print(int a[],int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
int main()
{
	int a[100];
	int i;
	srand(time(NULL));
	for(i=0;i<100;i++)
		a[i]=rand()%100;
	print(a,100);
	quicksort(a,0,99);
	print(a,100);
	return 0;
}
