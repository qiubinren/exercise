#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[])
{
	char s[100];
	char s1[100][100];
	fgets(s,99,stdin);
	int i=0,sum=0,flag=0,j;
	while(s[i])
	{
		if(flag==0&&s[i]!=' ')
		{
			flag=1;
			j=i;
		}
		else if(flag==1&&s[i]==' ')
		{
			s[i]=0;
			strncpy(s1[sum],s+j,i-j);
			sum++;
			flag=0;
		}
		i++;
	}
	if(flag==1)
	{
		strncpy(s1[sum],s+j,i-j);
		sum++;
	}
	printf("%d\n",sum);
	for(i=0;i<sum;i++)
		puts(s1[i]);
	return 0;
}
