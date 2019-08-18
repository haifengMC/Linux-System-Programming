#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t sem1, sem2;

void printer(const char*const &str)
{
	const char* strTemp = str;
	while (true)
	{
		if (0 == *strTemp) break;
		putchar(*strTemp++);
		fflush(stdout);
		sleep(1);
	}
	cout << endl;
}

void* threadProc1(void* str)
{
	while (true)
	{
		sem_wait(&sem1);
		printer((char*)str);
		int sval;
		sem_getvalue(&sem1, &sval);
		if (0 == sval)
			sem_post(&sem2);
	}
}
void* threadProc2(void* str)
{
	while (true)
	{
		sem_wait(&sem2);
		printer((char*)str);
		sem_post(&sem1);
		sem_post(&sem1);
	}
}


int main()
{
	sem_init(&sem1, 0, 2);
	sem_init(&sem2, 0, 0);

	pthread_t thd1, thd2;

	pthread_create(&thd1, 0, threadProc1, (void*)"hello");
	pthread_create(&thd2, 0, threadProc2, (void*)"world");

	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);

	sem_destroy(&sem1);
	sem_destroy(&sem2);

	return 0;
}
