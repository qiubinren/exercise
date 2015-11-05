#include <iostream>
#include "Complex.h"

using namespace std;

int main()
{
	Complex a(1,1);
	Complex b(2,1);
	a+=b;
	cout<<a<<endl;
	cout<<b<<endl;
	cout<<a+b<<endl;
	cout<<a+1.0<<endl;
	cout<<10+a<<endl;
	return 0;
}
