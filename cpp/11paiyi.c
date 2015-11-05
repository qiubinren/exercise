#include <stdio.h>
int main()
{
	int i;
	int s=0;
	int a[9]={1,1,2,2,3,3,4,4,6};
	for(i=0;i<9;i++)
		s^=a[i];
	printf("%d\n",s);
	return 0;
}
