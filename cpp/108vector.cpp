#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> a;
	vector<int> b(10);
	vector<int> c(10,5);
	vector<int> d(c);
	vector<int> e(c.begin()+1,c.end()-1);
	a.push_back(10);
	a.push_back(9);
	a.insert(a.begin(),8);
	a.insert(a.begin(),3,5);
	vector<int>::iterator it;
	for(it = a.begin(); it!=a.end();it++)
		cout<<*it<<' ';
	cout<<endl;
	for(it = d.begin(); it!=d.end();it++)
		cout<<*it<<' ';
	cout<<endl;
	for(it = e.begin(); it!=e.end();it++)
		cout<<*it<<' ';
	cout<<endl;
	a.pop_back();
	vector<int>::reverse_iterator rit;
	for(rit = a.rbegin(); rit!=a.rend();rit++)
		cout<<*rit<<' ';
	cout<<endl;
	it = a.begin();
	while(a.size()!=1)
	{
		it = a.erase(it);
	}
	for(rit = a.rbegin(); rit!=a.rend();rit++)
		cout<<*rit<<' ';
	cout<<endl;
	b.push_back(6);
	b.push_back(7);
	b.push_back(3);
	it = find(b.begin(),b.end(),7);
	for(;it!=b.end();++it)
		cout<<*it<<' ';
	cout<<endl;
		
	
}
