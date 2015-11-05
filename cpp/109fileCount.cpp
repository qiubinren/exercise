#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	map<string,int>	a;
	map<string,int>	c;
	string b;
	ifstream fin1("test1");
	while(!fin1.eof())
	{
		getline(fin1,b);
		int pos=0;
		while((pos = b.find_first_of(",.? !:"))!=string::npos)
		{
			c[b.substr(0,pos)]=1;
			b = b.erase(0,pos+1);
		}
	}
	map<string,int>::iterator it;
	fin1.close();
	ifstream fin2("test2");
	while(!fin2.eof())
	{
		getline(fin2,b);
		int pos=0;
		while((pos = b.find_first_of(",.? 	!:"))!=string::npos)
		{
			if(c[b.substr(0,pos)]!=1)
				a[b.substr(0,pos)]++;
			b = b.erase(0,pos+1);
		}
	}
	fin2.close();
	for(it = a.begin(); it!=a.end();it++)
		cout<<it->first<<' '<<it->second<<endl;
	return 0;
}
