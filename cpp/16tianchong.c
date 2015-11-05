#include <stdio.h>
int main()
{
	char s[100];
	fgets(s,99,stdin);
	int i=0;
	while(s[i])
	{
		if(s[i]==' ')
			s[i]='*';
		i++;
	}
	puts(s);
	return 0;
}
