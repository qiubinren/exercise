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
	bool operator () (string& a)
	{
		return a.size()>6;
	}
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
	copy_if(vec.begin(),vec.end(),ostream_iterator<string>(cout," "),isNum());
	cout<<endl;
	return 0;
}
