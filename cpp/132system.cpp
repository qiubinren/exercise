#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstdlib>

using namespace std;

int main()
{
	system("ls -l");
	return 0;
}
