#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
	pid_t pid = fork();

	switch (pid)
	{
	case -1:
		return 1;
	case 0:
		sleep(3);
		cout << "child exit" << endl;
		return 0;
	default:
		sleep(6);
		cout << "father exit" << endl;
		break;
	}


	return 0;
}