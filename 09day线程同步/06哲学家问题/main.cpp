#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define THREAD_NUM 5

pthread_mutex_t mutexArr[THREAD_NUM], ;

void* threadProc(void* param)
{
	int i = *(int*)&param;
	while (true)
	{
		pthread_mutex_lock(&mutexArr[(i + 1) % THREAD_NUM]);
		//cout << "mutex["<< i <<"]: " << (i + 1) % THREAD_NUM << " ok" << endl;
		pthread_mutex_lock(&mutexArr[i]);
		//cout << "mutex[" << i << "]: " << i << " ok" << endl;

		cout << "thread: " << i << " ok" << endl;

		pthread_mutex_unlock(&mutexArr[i]);

		sleep(1);

		pthread_mutex_unlock(&mutexArr[(i + 1) % THREAD_NUM]);

		sleep(1);
	}

	return NULL;
}

int main()
{
	pthread_t threadArr[THREAD_NUM];

	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_mutex_init(&mutexArr[i], NULL);
	}
	pthread_mutex_lock(&mutexArr[0]);
	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_create(threadArr + i, NULL, threadProc, (void*)i);
		sleep(1);
	}
	pthread_mutex_unlock(&mutexArr[0]);

	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_join(threadArr[i], NULL);
	}
	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_mutex_destroy(&mutexArr[i]);
	}


	return 0;
}