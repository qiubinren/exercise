#include <stdio.h>
int main()
{
	int a;
	scanf("%d",&a);
	int s=0;
	while(a)
	{
		a=a&(a-1);
		++s;
	}
	printf("%d\n",s);
	return 0;
}
