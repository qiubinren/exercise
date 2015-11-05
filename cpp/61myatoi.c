#include <stdio.h>
int main()
{

	char s[32];
	int f=1,sum=0;
	gets(s);
	int i=0;
	if(s[0]=='-')
	{
		i++;
		f=-1;
	}
	for(;s[i]!=0;i++)
	{
		sum=sum*10+s[i]-48;
	}
	printf("%d\n",f*sum);
	return 0;
}
