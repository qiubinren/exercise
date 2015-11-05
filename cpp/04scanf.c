#include <stdio.h>
int main()
{
	char e[10];
	scanf("%s",e);
	char a;
	while((a=getchar())!='\n'&&a!=EOF);
	char b=getchar();
	printf("%s,%c",e,b);
	return 0;
}
