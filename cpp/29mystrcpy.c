#include <stdio.h>
int mystrcpy(char* a,char* b)
{
	int i=0;
	while(b[i])
	{
		a[i]=b[i];
		i++;
	}
	a[i]=0;
}
int main()
{
	char a[100],b[100];
	gets(a);
	gets(b);
	mystrcpy(a,b);
	puts(a);
	return 0;
}
