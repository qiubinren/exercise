#include <stdio.h>
int main()
{
	int x=0;
	int a[4];
	scanf("%d.%d.%d.%d",&a[3],&a[2],&a[1],&a[0]);
	int sum=(a[3]<<24)|(a[2]<<16)|(a[1]<<8)|a[0];
	unsigned char* s=(unsigned char*)&sum;
	printf("%u.%u.%u.%u\n",*(s+3),*(s+2),*(s+1),*s);
	return 0;
}
