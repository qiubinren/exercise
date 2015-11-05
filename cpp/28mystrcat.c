#include <stdio.h>
int mystrcat(char *a,char *b)
{
	int i=0;
	while(a[i++]);
	i--;
	int j=0;
	while(b[j])
	{
		a[i+j]=b[j];
		j++;
	}
	a[i+j]='\0';
}
int main()
{
	char a[200],b[100];
	gets(a);
	gets(b);
	mystrcat(a,b);
	puts(a);
	return 0;
}
