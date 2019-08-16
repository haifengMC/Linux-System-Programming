#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

int main()
{
	pid_t pid;
	int i;
	for (i = 0; i < 7; i++)
	{
		pid = vfork();
		if (0 == pid)break;
	}

	switch (i)
	{
	case 0:
		execl("./a.out", "./a.out", "0", NULL);
		cout << "execl" << endl;
		exit(0);
	case 1:
		execlp("./a.out", "a.out", "1", NULL);
		cout << "execlp" << endl;
		exit(1);
	case 2:
		execle("./a.out", "./a.out", "2", NULL);
		cout << "execle" << endl;
		exit(2);
	case 3:
		{
			char*const arg[] = { (char*)"./a.out", (char*)"3", NULL};
			execv("./a.out", arg);
			cout << "execv" << endl;
			exit(3);
		}
	case 4:
		{
			char*const arg[] = { (char*)"./a.out", (char*)"4", NULL };
			execvp("./a.out", arg);
			cout << "execvp" << endl;
			exit(4);
		}
	case 5:
		{
			char*const arg[] = { (char*)"./a.out", (char*)"5", NULL };
			execvpe("./a.out", arg, NULL);
			cout << "execvpe" << endl;
			exit(5);
		}
	case 6:
		{
			char*const arg[] = { (char*)"./a.out", (char*)"6", NULL };
			execve("./a.out", arg, NULL);
			cout << "execve" << endl;
			exit(6);
		}
	case 7:
		while (1)
		{
			int status;
			pid = wait(&status);
			if (-1 == pid) return 0;
			if (WIFEXITED(status))
				cout << pid << " " << 
				WEXITSTATUS(status) << endl;
		}
		break;
	default:
		break;
	}

	pause();

	return 0;
}