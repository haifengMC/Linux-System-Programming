#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define p(X) cout << #X" : " << X << endl; 

//#define WAIT
#define WAITPID

int main()
{
	pid_t pid = 1;
	for (int i = 0; i < 2; i++)
	{
		if (0 == pid)break;
		pid = fork();
	}
	int status;
	switch (pid)	
	{	
	case -1:
		_exit(1);
		break;
	case 0:
		_exit(2);
	default:
#ifdef WAIT
		sleep(1);

		pid_t pid = wait(&status);
		p(pid);
		if (WIFEXITED(status)) p(WEXITSTATUS(status));
		if (WIFSIGNALED(status)) p(WTERMSIG(status));
		if (WIFSTOPPED(status)) p(WSTOPSIG(status));

#endif // WAIT

#ifdef WAITPID

		while (true)
		{
			switch (pid = waitpid(-1, &status, WNOHANG))
			{
			case -1:
				return -1;
			case 0:
				cout << "wait child" << endl;
				break;
			default:
				if (WIFEXITED(status))
				{
					p(pid);
					p(WEXITSTATUS(status));
				}
				if (WIFSIGNALED(status))
				{
					p(pid);
					p(WTERMSIG(status));
				}
				if (WIFSTOPPED(status))
				{
					p(pid);
					p(WSTOPSIG(status));
				}
				break;
			}
		}

#endif // WAITPID




		
		break;
	}

	return 0;
}