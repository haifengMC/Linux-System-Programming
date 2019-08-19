#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

//#define ALRM
#define TIMER

using namespace std;

void timerSig(int)
{
	cout << "hello" << endl;
}


int main()
{
#ifdef ALRM
	int seconds = 0;

	seconds = alarm(5);
	printf("seconds = %d\n", seconds);

	sleep(2);
	seconds = alarm(5);
	printf("seconds = %d\n", seconds);

#endif // ALRM

#ifdef TIMER
	itimerval newTime = { {1, 0},{2, 0} };
	signal(SIGALRM, timerSig);
	setitimer(ITIMER_REAL, &newTime, NULL);
#endif // TIMER

	while (1);

	return 0;
}