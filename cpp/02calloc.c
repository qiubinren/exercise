#include <stdio.h>
#include <stdlib.h>
int main()
{
	int *p=calloc(1,sizeof(int));
	printf("%d\n",*p);
	free(p);
	return 0;
}
