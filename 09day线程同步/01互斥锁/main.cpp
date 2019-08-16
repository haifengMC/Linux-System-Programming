#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex;

void printer(char* str)
{
	pthread_mutex_lock(&mutex);
	while (0 != *str)
	{
		putchar(*str++);
		fflush(stdout);
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
}

void* threadProc1(void*)
{
	printer("hello\n");
	return NULL;
}

void* threadProc2(void*)
{
	printer("world\n");
	return NULL;
}

int main()
{

	pthread_mutex_init(&mutex, NULL);


	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, threadProc1, NULL);
	pthread_create(&thread2, NULL, threadProc2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);


	pthread_mutex_destroy(&mutex);

	return 0;
}

