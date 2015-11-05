#include <iostream>
using namespace std;
template <typename T>
void createDymamicArray(T **&p,int row,int col)
{
	p = new T*[row];
	for(int i=0;i<row;i++)
	{
		p[i]=new T[col];
	}
}
template <typename T>
T** destroyDymamicArray(T** a,int row)
{
	for(int i=0;i<row;i++)
		delete []a[i];
	delete []a;
	return NULL;
}
int main()
{
	int **p =NULL; 
	 createDymamicArray(p,2,3);
	for(int i=0;i<2;i++)
		for(int j=0;j<3;j++)
		{
			p[i][j]=i*3+j;
			cout<<p[i][j]<<endl;
		}	
	p=destroyDymamicArray(p,2);	
	return 0;
}
