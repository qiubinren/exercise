#include <stdio.h>
int main()
{
	int a[4];
	scanf("%d.%d.%d.%d",&a[3],&a[2],&a[1],&a[0]);
	int ip=(a[3]<<24)|(a[2]<<16)|(a[1]<<8)|a[0];
	unsigned char* q=(unsigned char*)&ip;
	printf("%u.%u.%u.%u\n",*(q+3),*(q+2),*(q+1),*q);
	return 0;
}

