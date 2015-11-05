#include <stdio.h>
int main()
{
	char a[12];
	fgets(a,11,stdin);
	int i=0;
	int s1=0,s2=0,s3=0;
	a[12]=0;
	while(a[i]!='\0')
	{
		if((a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z'))
			s1++;
		else if(a[i]==' ')
			s2++;
		else if(a[i]>='0'&&a[i]<='9')
			s3++;
		i++;
	}
	printf("%d,%d,%d\n",s1,s2,s3);
	return 0;
}
