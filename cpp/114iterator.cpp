#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

class CString
{
public:
	CString(const char* str = NULL);	
	CString(const CString& str);	
	~CString();
	friend ostream & operator << (ostream& out,const CString& str);
	friend istream & operator >> (istream& in,CString& str);
	CString& operator = (const char*& str);		
	CString& operator = (const CString& str);		
	CString operator + (const CString& str)const;
	CString operator + (const char*& str)const;
	bool operator == (const char* str)const;
	bool operator == (const CString& str)const;
	const char operator [] (int i)const;
	size_t size()const;
	class CIterator;
	friend class CIterator;
	class CIterator
	{
	public:
		CIterator(CString& a):str(a)
		{
			i=0;
		}
		~CIterator()
		{
		}
		CString& operator * ()
		{
			return str;
		}
		CString* operator ->()
		{
			return &str;
		}
	private:
		int i;
		CString& str;
	};
private:
	char *m_str;
};
CString::CString(const char* str)
{
	if(!str)
		m_str = NULL;
	else{
		m_str =new char[strlen(str)+1];
		strcpy(m_str,str);
	}
}
CString::CString(const CString& str)
{
	if(!str.m_str)
		m_str = NULL;
	else
	{
		m_str = new char(strlen(str.m_str)+1);
		strcpy(m_str,str.m_str);
	}
}
CString::~CString()
{
	delete []m_str;
}
ostream & operator << (ostream& out,const CString& str)
{
	out << str.m_str;
	return out;
}
istream & operator >> (istream& in,CString& str)
{
	char temp[255];
	in >> setw(255)>>str.m_str;
	str = temp;
	return in;
}
CString& CString::operator = (const char*& str)
{
	delete []m_str;
	if(!str)
		m_str=NULL;
	else{
		m_str = new char[strlen(str)+1];
		strcpy(m_str,str);
	}
	return *this;
}
CString& CString::operator = (const CString& str)
{
	delete []m_str;
	if(!str.m_str)
		m_str=NULL;
	else{
		m_str = new char[strlen(str.m_str)+1];
		strcpy(m_str,str.m_str);
	}
	return *this;
}
CString CString::operator + (const CString& str)const
{
	CString newString;
	if(!str.m_str)
		newString = *this;
	else if(!m_str)
		newString = str;
	else{
		newString = new char[strlen(m_str)+strlen(str.m_str)+1];
		strcpy(newString.m_str,m_str);
		strcat(newString.m_str,str.m_str);
	}
	return newString;
}
CString CString::operator + (const char*& str)const
{
	CString newString;
	if(!m_str)
		newString = *this;
	else if(!m_str)
		newString = str;
	else{
		newString = new char[strlen(m_str)+strlen(str)+1];
		strcpy(newString.m_str,m_str);
		strcat(newString.m_str,str);
	}
	return newString;
}
bool CString::operator == (const char* str)const
{
	if(strlen(str)!=strlen(m_str))
		return false;
	return strcmp(m_str,str)?false:true;
}
bool CString::operator == (const CString& str)const
{
	if(strlen(m_str)!=strlen(str.m_str))
		return false;
	return strcmp(m_str,str.m_str)?false:true;
}
size_t CString::size()const
{
	return strlen(m_str);
}
const char CString::operator [] (int i)const
{
	return m_str[i];
}
int main()
{
	CString a("wo");
	CString b=a+b;
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
	cout<<d.size()<<endl;
	cout<<a[1]<<endl;
	CString::CIterator it(a);
	cout<<*it<<endl;
	cout<<it->size()<<endl;
	return 0;
}
