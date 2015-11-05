#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("Usage:%s filename1 filename2\n",argv[0]);
		return 0;
	}
	string temp;
	ifstream fi(argv[1]);	
	ofstream fo(argv[2]);
	while(!fi.eof())
	{
		getline(fi,temp);
		fo<<temp<<endl;	
	}
	return 0;
}

