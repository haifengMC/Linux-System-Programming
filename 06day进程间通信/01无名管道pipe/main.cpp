#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main()
{
	int pipefd[2];
	if (-1 == pipe(pipefd)) return 1;

	pid_t pid = fork();

	switch (pid)
	{
	case -1:
		cout << "fork err" << endl;
		break;
	case 0:
		while (true)
		{
			write(pipefd[1], "this is a child", 15);
			sleep(2);
		}
		break;
	default:
		while (true)
		{
			char buf[20] = { 0 };
			read(pipefd[0], buf, sizeof(buf) - 1);
			cout << buf << endl;
			sleep(3);
		}
		break;
	}



	return 0;
}