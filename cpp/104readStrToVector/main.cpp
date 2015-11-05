#include <iostream>
#include <vector>
using namespace std;
int main()
{
	string str;
	vector<string> Str;
	getline(cin,str);
	int pos;
	while((pos = str.find_first_of(",.? !: 	",0))!=string::npos)
	{
		Str.push_back(str.substr(0,pos));
		str.erase(0,pos+1);	
	}
	Str.push_back(str);
	vector<string>::iterator it;
	for(it=Str.begin();it!=Str.end();it++)
		cout<<*it<<endl;
	return 0;
}
