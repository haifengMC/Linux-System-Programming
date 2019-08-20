#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;


//#define SIGHANDLER
#define SIGACTION

int main()
{
	struct sigaction sa;

#ifdef SIGHANDLER
	sa.sa_flags = 0;
	sa.sa_handler = [](int)
	{
		printf("SIGQUIT\n");
		sleep(5);
		printf("week up...\n");
	};
#endif // SIGHANDLER
#ifdef SIGACTION
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = [](int, siginfo_t*, void*)
	{
		printf("SIGQUIT\n");
		sleep(5);
		printf("week up...\n");
	};
#endif // SIGACTION


	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);

	sigaction(SIGQUIT, &sa, NULL);

	while (true)
	{

	}

	return 0;
}