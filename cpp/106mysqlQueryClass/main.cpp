#include <iostream>
#include "Query.h"
using namespace std;
class dt
{
public:
	string a;
	string b;
};
int main()
{
	Query stream;
	dt a;
	if(!stream.IsConnect())
		stream.Connect("localhost", "root", "", "test2", 0);
	stream.ExecSql("select * from test;");
	while(!stream.eof())
	{
		stream >>  a.a >> a.b; 
		cout<< a.a <<' '<<a.b<<endl;
	}
	return 0;
}
