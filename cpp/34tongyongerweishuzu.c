#include <stdio.h>
#include <stdlib.h>
int create(int (*a)[10],int m,int n)/*int *a             int a[][n]*/
{
	int i;
	a=malloc(m*n*sizeof(int));
	return 0;
}
int print(int a[][10],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
}
int main()
{
	int a[10][10];
	int m=10,n=10;
	create(a,10,10);/**a                                 a*/
	print(a,m,n);
	return 0;
}
