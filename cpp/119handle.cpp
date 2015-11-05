#include <iostream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

class animal
{
public:
	animal()
	{
	}
	animal(string &name)
	{
		m_name = name;
	}
	animal(const char* p)
	{
		m_name = p;
	}
	virtual ~animal(){}
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
	~Cat(){}
	void sound()
	{
		cout<<m_name<<" miao miao~~"<<endl;
	}
};
class Dog:public animal
{
public:
	Dog(string& name):animal(name){}
	Dog(const char* p):animal(p){}
	~Dog(){}
	void sound()
	{
		cout<<m_name<<" wang wang~~"<<endl;
	}
};
class Chicken:public animal
{
public:
	Chicken(string& name):animal(name){}
	Chicken(const char* p):animal(p){}
	virtual ~Chicken(){}
	void sound()
	{
		cout<<m_name<<" wo wo wo~~"<<endl;
	}
};

class handle
{
public:
	handle()
	{
		m_ptr=NULL;	
	}
	handle(animal& a)
	{
		m_ptr = new animal;
		*m_ptr = a;
	}
	~handle()
	{
		delete m_ptr;
		m_ptr = NULL;
	}
	animal * operator ->()
	{
		return m_ptr;
	}
	handle& operator = (handle &a)
	{
		delete m_ptr;
		m_ptr = new animal;
		*m_ptr = *(a.m_ptr);
		return *this;
	}
	handle& operator = (animal &a)
	{
		delete m_ptr;
		m_ptr = new animal;
		*m_ptr = a;
		return *this;
	}
private:
	animal *m_ptr;
};

int main()
{
	handle vec[3];
        Cat a("mimi");
        Dog b("alin");
        Chicken c("guoguo");
        vec[0]=a;
        vec[1]=b;
        vec[2]=c;
        for(int i=0;i<3;i++)
                vec[i]->sound();
        return 0;
}
