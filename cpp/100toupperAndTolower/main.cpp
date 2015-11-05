#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
char toul(char c)
{
	if(c>='A'&&c<='Z')
		return c+32;
	if(c>='a'&&c<='z')
		return c-32;
}
int main()
{
	string a="adfdffdafaAFADaf";
	transform(a.begin(),a.end(),a.begin(),toul);
	cout<<a<<endl;
	return 0;
}
