#include <iostream>
#include <memory>
using namespace std;

class Person
{
public:
	Person()
	{
		cout<<"Person()"<<endl;
	}
	~Person()
	{
		cout<<"~Person()"<<endl;
	}
	void print()
	{
		cout<<"print"<<endl;
	}
};

template<typename T>
class AutoPtr
{
public:
	AutoPtr()
	{
		a=NULL;
	}
	AutoPtr(T* m)
	{
		a=m;
	}
	void* operator new (size_t a)
	{
		return NULL;
	}
	T*& get()
	{
		return a;
	}
	T& operator * ()
	{
		return *a;
	}
	T*& operator -> ()
	{
		return a;
	}
private:
	T *a;	
};

int main()
{
	auto_ptr<Person> ptr(new Person);
	AutoPtr<Person> pt(new Person);
	if(pt.get())
	{
		pt->print();
		(*pt).print();
	}
	if(ptr.get())
	{
		ptr->print();	
		(*ptr).print();
	}
	return 0;
}

