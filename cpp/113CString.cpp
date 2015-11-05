#include <iostream>
#include <cstring>

using namespace std;

class CString
{
public:
	CString(const char* cstr = 0);
	CString(const CString& str);
	CString& operator = (const CString& str);
	CString operator + (const CString& str)const;
	CString operator + (const char* cstr)const;
	bool operator == (const CString& str)const;
	bool operator == (const char* cstr)const;
	char operator [](int i)const
	{
		return m_data[i];
	}
	~CString();
	char* get_c_str() const	
	{
		return m_data;
	}
	int size() const
	{
		return n;
	}
private:
	int n;
	char *m_data;
};
inline CString::CString(const char* cstr)
{
	if(cstr)
	{
		n = strlen(cstr);
		m_data = new char[n+1];
		strcpy(m_data, cstr);
	}
	else
	{
		n = 0;
		m_data = new char[1];	
		*m_data = 0;
	}
}
inline CString::~CString()
{
	delete []m_data;
}
inline CString::CString(const CString& str)
{
	n = strlen(str.m_data);
	m_data = new char[n+1];
	strcpy(m_data, str.m_data);
}
inline CString & CString::operator = (const CString& str)
{
	if(this == &str)
		return *this;
	delete []m_data;
	n = strlen(str.m_data);
	m_data = new char[n+1];
	strcpy(m_data, str.m_data);
	return *this;
}
inline CString  CString::operator +(const CString& str) const
{
	char *tmp = new char[n+str.n+1];
	strcpy(tmp, m_data);
	strcat(tmp, str.m_data);
	CString tmpstr(tmp);
	delete []tmp;
	return tmpstr;
}
inline CString  CString::operator +(const char* cstr)const
{
	char *tmp = new char[n+strlen(cstr)+1];
	strcpy(tmp, m_data);
	strcat(tmp, cstr);
	CString tmpstr(tmp);
	delete []tmp;
	return tmpstr;
}
CString operator +(const char* cstr,const CString& str)
{
	char *tmp = new char[strlen(cstr)+str.size()+1];
	strcpy(tmp, cstr);
	strcat(tmp, str.get_c_str());
	CString tmpstr(tmp);
	delete []tmp;
	return tmpstr;
}
inline bool CString::operator == (const CString& str)const
{
	return strcmp(m_data, str.m_data)?false:true;
}
inline bool CString::operator == (const char* cstr)const
{
	return strcmp(m_data, cstr)?false:true;
}
bool operator ==(const char* cstr,const CString& str)
{
	return strcmp(cstr,str.get_c_str())?false:true;
}

ostream& operator << (ostream& os, const CString& str)
{
	os<<str.get_c_str();
	return os;
}
	
int main()
{
	CString a("wo");
	CString b=a;
	CString c(b);
	CString d="adf";
	cout<<a<<endl;
	cout<<b<<endl;
	cout<<c<<endl;
	cout<<d<<endl;
	cout<<(a+b)<<endl;
	cout<<(a==b)<<endl;
	cout<<(b==d)<<endl;
	cout<<(c+d)<<endl;
	cout<<(c+"shi")<<endl;
	cout<<("shi"+c)<<endl;
	cout<<d.size()<<endl;
	cout<<a[1]<<endl;
	return 0;
}
