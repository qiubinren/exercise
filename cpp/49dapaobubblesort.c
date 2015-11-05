#include <stdio.h>
int myswap(int a[],int i,int j)
{
	int x;
	x=a[i];
	a[i]=a[j];
	a[j]=x;
	return 0;
}
int bubblesort(int a[],int left,int right)
{
		while(left<right)
		{
				int i;
				for(i=left;i<right-1;i++)
					if(a[i]>a[i+1])
						myswap(a,i,i+1);
				right--;
				for(i=right-1;i>left;i--)
					if(a[i]<a[i-1])
						myswap(a,i,i-1);
				left++;
		}
		return 0;
}
int print(int a[],int n)
{
	int i;
	for(i=0;i<10;i++)
		printf("%d\n",a[i]);
	return 0;
}
int main()
{
		int a[10]={1,2,6,5,0,9,8,3,4,7};
		print(a,10);
		bubblesort(a,0,10);
		print(a,10);
		return 0;
}
