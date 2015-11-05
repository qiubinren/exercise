#include <iostream>
using namespace std;

class smallInt 
{
public:
	smallInt()
	{
	}
	smallInt(int a)
	{
		this->a = a;
	}
	smallInt(const smallInt& t)
	{
		a = t.a;	
	}
	~smallInt(){}
	smallInt& operator = (const smallInt& t)
	{
		a = t.a;
		return *this;
	} 
	smallInt operator + (const smallInt& t)const
	{
		return smallInt(a+t.a);
	}
	smallInt operator * (const smallInt& t)const
	{
		return smallInt(a*t.a);
	}
	smallInt operator / (const smallInt& t)const
	{
		return smallInt(a/t.a);
	}
	smallInt operator - (const smallInt& t)const
	{
		return smallInt(a-t.a);
	}
	smallInt operator % (const smallInt& t)const
	{
		return smallInt(a%t.a);
	}
	smallInt operator ++()
	{
		++a;
		return smallInt(a);
	}
	smallInt operator ++(int)
	{
		int temp=a;
		++a;
		return smallInt(temp);
	}
	friend istream& operator >>(istream& in,smallInt& a);
	friend ostream& operator <<(ostream& out,const smallInt& a);
private:
	int a;	
};
istream& operator >>(istream& in,smallInt& a)
{
	in >> a.a;
	return in;
}
ostream& operator <<(ostream& out,const smallInt& a)
{
	out << a.a;
	return out;
}

int main()
{
	smallInt c1(2),c2(3),c3;
	c3 = c1 + c2;
	cout << c3 << endl;
	c3 = c1 * c2;
	cout << c3 << endl;
	c3 = c1 - c2;
	cout << c3 << endl;
	c3 = c1 / c2;
	cout << c3 << endl;
	c3 = c1 % c2;
	cout << c3 << endl;
	cin >> c3;
	cout<<c3<<endl;
	cout<<++c3<<endl;
	cout<<c3++<<endl;
	cout<<c3<<endl;
	return 0;
}
