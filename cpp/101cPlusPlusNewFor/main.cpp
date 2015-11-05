#include <iostream>
using namespace std;
template <typename T>
void newfor(const T& d)
{
	for(auto c:d)
		cout<<c<<endl;
}
int main()
{
	string a="dfaf";
	int b[4]={0,3,3,4};
	newfor(a);
	newfor(b);
	return 0;
}
