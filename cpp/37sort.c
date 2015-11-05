#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int a[100000];
int b[100000];
int insertsort()
{
	int i=1;
	int j;
	while(i<100000)
	{
		j=i-1;
		int x=b[i];
		while(j>=0&&x>b[j])
		{
			b[j+1]=b[j];
			--j;
		}
		j=j+1;
		b[j]=x;
		i++;
	}
	return 0;
}
int bubblesort()
{
	int i,j;
	for(i=1;i<100000;i++)
	{
		for(j=0;j<100000-i;j++)
			if(b[j]>b[j+1])
			{
				int x=b[j];
				b[j]=b[j-1];
				b[j-1]=x;
			}
	}
	return 0;
}
int selectsort()
{
	int i,j;
	for(i=0;i<100000;i++)
	{
		int x=i;
		for(j=i+1;j<100000;j++)
			if(b[x]>b[j])
				x=i;
		if(x!=i)
		{
			int x1=b[x];
			b[x]=b[i];
			b[i]=x1;
		}
	}
	return 0;
}
int shellsort()
{
	int i,j,k;
	for(k=100000/2;k>0;k/=2)
	{
		for(i=k;i<100000;i+=k)
		{
			for(j=i-k;j>0;j-=k)
			{
				if(b[j+k]<b[j])
				{
					int x=b[j+k];
					b[j+k]=b[j];
					b[j]=x;
				}
			}
		}
	}
	return 0;
}
int quicksort(int a[],int l,int r)
{
	if(l>=r)
	{
		int mid=(l+r)/2;
		int x=a[mid];
		a[mid]=a[l];
		int i=l,j=r;
		while(i<j)
		{
			while(i<j&&a[j]>x)
				j--;
			if(i<j)
				a[i]=a[j];
			while(i<j&&a[i]<x)
				i++;
			if(i<j)
				a[j]=a[i];
		}
		a[i]=x;
		quicksort(a,l,i-1);
		quicksort(a,i+1,r);
	}
	return 0;
}
int main()
{
	size_t t1;
	size_t t2;
	srand(time(NULL));
	int i;
	for(i=0;i<100000;i++)
	{
		a[i]=rand();
		b[i]=a[i];
	}
	
	for(i=0;i<100000;i++)
	{
		b[i]=a[i];
	}
	t1=time(NULL);
	insertsort();
	t2=time(NULL);
	printf("insert:%d\n",t2-t1);
	for(i=0;i<100000;i++)
		b[i]=a[i];
	
	
	for(i=0;i<100000;i++)
	{
		b[i]=a[i];
	}
	 t1=time(NULL);
	bubblesort();
	t2=time(NULL);
	printf("bubble:%d\n",t2-t1);
	
	
	for(i=0;i<100000;i++)
	{
		b[i]=a[i];
	}
 	t1=time(NULL);
	selectsort();
	t2=time(NULL);
	printf("select:%d\n",t2-t1);
	
	for(i=0;i<100000;i++)
	{
		b[i]=a[i];
	}
	t1=time(NULL);
	shellsort();
	t2=time(NULL);
	printf("shell:%d\n",t2-t1);
	
	for(i=0;i<100000;i++)
	{
		b[i]=a[i];
	}
	t1=time(NULL);
	quicksort(b,0,100000);
	t2=time(NULL);
	printf("quick:%d\n",t2-t1);
	return 0;	
	}
