#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
	cout << ttyname(STDIN_FILENO) << endl;
	cout << ttyname(STDOUT_FILENO) << endl;
	cout << ttyname(STDERR_FILENO) << endl;


	return 0;
}