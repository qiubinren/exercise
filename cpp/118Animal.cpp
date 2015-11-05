#include <iostream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

class animal
{
public:
	animal(string &name)
	{
		m_name = name;
	}
	animal(const char* p)
	{
		m_name = p;
	}
	virtual void sound()
	{
		cout<<m_name<<" speak "<<endl;
	}	
	animal& operator = (animal& temp)
	{
		m_name = temp.m_name;
	}
	
protected:
	string m_name;
};

class Cat:public animal
{
public:
	Cat(string& name):animal(name){}
	Cat(const char* p):animal(p){}
	virtual void sound()
	{
		cout<<m_name<<" miao miao~~"<<endl;
	}
};
class Dog:public animal
{
public:
	Dog(string& name):animal(name){}
	Dog(const char* p):animal(p){}
	virtual void sound()
	{
		cout<<m_name<<" wang wang~~"<<endl;
	}
};
class Chicken:public animal
{
public:
	Chicken(string& name):animal(name){}
	Chicken(const char* p):animal(p){}
	virtual void sound()
	{
		cout<<m_name<<" wo wo wo~~"<<endl;
	}
};

int main()
{
	vector<animal> vec;
	Cat a("mimi");
	Dog b("alin");
	Chicken c("guoguo");
	vec.push_back(a);
	vec.push_back(b);
	vec.push_back(c);
	vector<animal>::iterator it;
	for(it=vec.begin();it!=vec.end();it++)
		it->sound();
	return 0;
}
