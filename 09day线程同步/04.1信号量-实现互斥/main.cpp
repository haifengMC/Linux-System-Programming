
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t sem;

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

void* threadProc(void* str)
{
	sem_wait(&sem);
	printer((char*)str);
	sem_post(&sem);
}


int main()
{
	sem_init(&sem, 0, 1);

	pthread_t thd1, thd2;

	pthread_create(&thd1, 0, threadProc, (void*)"hello");
	pthread_create(&thd2, 0, threadProc, (void*)"world");

	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);

	sem_destroy(&sem);

	return 0;
}
