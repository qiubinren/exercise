#include <stdio.h>
int a[10],i=-1;
int push(int x)
{
	a[++i]=x;
	return 0;
}
int pop()
{
	i--;
	return 0;
}
int top()
{
	return a[i];
}
int empty()
{
	if(i==-1)
		return 1;
	else
		return 0;
}
int main()
{
	int x;
	scanf("%d",&x);
	while(x!=0)
	{
		push(x);
		scanf("%d",&x);
	}
	while(!empty())
	{
		printf("%d\n",top());
		pop();
	}
	return 0;
}
