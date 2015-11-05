#include <stdio.h>
int he(const int a,const int b)
{
	return a+b;
}
int cha(const int a,const int b)
{
	return a-b;
}
int ji(const int a,const int b)
{
	return a*b;
}
int shang(const int a,const int b)
{
	return a/b;
}
int main()
{
	int a,b;
	scanf("%d %d",&a,&b);
	int (*func)(const int,const int);
	func=he;
	printf("%d\n",func(a,b));
	func=cha;
	printf("%d\n",func(a,b));
	func=ji;
	printf("%d\n",func(a,b));
	func=shang;
	printf("%d\n",func(a,b));
	return 0;
}
