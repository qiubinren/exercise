#include <stdio.h>
#include <string.h>
int mystrlen(char* a)
{
	int i=0;
	while(a[i])
		i++;
	return i;
}
int main()
{
	char a[100];
	gets(a);
	printf("%d\n",mystrlen(a));
	printf("%d\n",strlen(a));
	return 0;
}
