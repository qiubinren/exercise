#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

class isNum
{
public:
	isNum():n(0){}
	isNum(int a):n(a){}
	bool operator () (string& a)
	{
		return a.size()>n;
	}
private:
	int n;
};

int main()
{
	ifstream in("test1");
	istream_iterator<string> beg(in);
	istream_iterator<string> end;
	vector<string> vec(beg,end);
	sort(vec.begin(),vec.end());
	vector<string>::iterator it;
	it = unique(vec.begin(),vec.end());
	vec.erase(it,vec.end());
	cout<<"please input the print word's length you want"<<endl;
	int n;
	cin>>n;
	copy_if(vec.begin(),vec.end(),ostream_iterator<string>(cout," "),isNum(n));
	cout<<endl;
	return 0;
}
