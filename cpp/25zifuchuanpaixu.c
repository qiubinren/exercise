#include <stdio.h>
#include <string.h>
int main()
{
	char a[100][100];
	int n;
	int i;
	scanf("%d",&n);
	getchar();
	for(i=0;i<n;i++)
		gets(a[i]);
	int j;
	for(i=0;i<n;i++)
	{
		int k=i;
		for(j=i;j<n;j++)
		{
			if(strcmp(a[j],a[k])<0)
				k=j;
		}
		if(k!=i)
		{
			char x[100];
			strcpy(x,a[k]);
			strcpy(a[k],a[i]);
			strcpy(a[i],x);
		}
	}
	for(i=0;i<n;i++)
		puts(a[i]);
	return 0;
}
