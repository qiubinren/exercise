#include <iostream>
using namespace std;

template <typename T>
void swap1(T *a,T *b)
{
	T c;
	c=*a;
	*a=*b;
	*b=c;
}

template <typename T>
void swap2(T &a,T &b)
{
	T c;
	c=a;
	a=b;
	b=c;
}
int main()
{
	int a=1,b=2;
	swap1(&a,&b);
	cout<<a<<b<<endl;
	swap2(a,b);
	cout<<a<<b<<endl;
}
