#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

int main()
{
	sigset_t newSet, oldSet;

	sigemptyset(&newSet);

	sigaddset(&newSet, SIGINT);
	sigaddset(&newSet, SIGQUIT);
	sigaddset(&newSet, SIGKILL);

	sigprocmask(SIG_BLOCK, &newSet, &oldSet);

	int i = 0;
	while (true)
	{
		sigset_t pend;
		sigpending(&pend);
		for (int j = 0; j < 32; j++)
		{
			if (1 == sigismember(&pend, j)) printf("1");
			else printf("0");
		}
		cout << endl;

		sleep(1);
		++i;
		if (10 < i)
		{
			sigprocmask(SIG_SETMASK, &oldSet, nullptr);
		}
	}


	return 0;
}