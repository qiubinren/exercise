#include <iostream>
#include <pthread.h>

using namespace std;

template<typename T>
class Singleton 
{
public:
	static T& Instance()
	{
		pthread_once(&once_control_, Singleton::init);
		return *value_;
	}
private:
	Singleton();
	~Singleton();
	static void init()
	{
		value_ = new T();
	}
private:
	static pthread_once_t once_control_;
	static T* value_;
};

template<typename T>
pthread_once_t Singleton<T>::once_control_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;

int main()
{
	Singleton<int>::Instance() = 2;
	cout<<Singleton<int>::Instance()<<endl;
	return 0;	
}
