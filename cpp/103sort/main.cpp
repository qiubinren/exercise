#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
template <typename T>
int Less(const T a,const T b)
{
	if(a<b)
		return 1;
	return 0;
}
template <typename T>
int More(const T a,const T b)
{
	if(a>b)
		return 1;
	return 0;
}
int main()
{
	vector<int> a;
	a.push_back(3);
	a.push_back(2);
	a.push_back(1);
	sort(a.begin(),a.end());
	vector<int>::iterator it;
	for(it=a.begin();it!=a.end();it++)
		cout<<*it<<endl;
	sort(a.begin(),a.end(),Less<int>);	
	for(it=a.begin();it!=a.end();it++)
		cout<<*it<<endl;
	sort(a.begin(),a.end(),More<int>);	
	for(it=a.begin();it!=a.end();it++)
		cout<<*it<<endl;
	sort(a.begin(),a.end(),less<int>());
	for(it=a.begin();it!=a.end();it++)
		cout<<*it<<endl;
	sort(a.begin(),a.end(),greater<int>());
	for(it=a.begin();it!=a.end();it++)
		cout<<*it<<endl;
	
	return 0;
}
