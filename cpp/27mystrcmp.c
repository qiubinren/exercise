#include <stdio.h>
#include <string.h>
int mystrcmp(char* a,char* b)
{
	int len;
	int i=0;
	len=strlen(a)>strlen(b)?strlen(b):strlen(a);
	while(i<len)
	{
		if(a[i]>b[i])
			return 1;
		else if(a[i]<b[i])
			return -1;
		i++;
	}
	if(a[i]!='\0')
		return 1;
	if(b[i]!='\0')
		return -1;
	return 0;
}
int main()
{
	char a[100],b[100];
	gets(a);
	gets(b);
	printf("%d\n",mystrcmp(a,b));
	return 0;
}
