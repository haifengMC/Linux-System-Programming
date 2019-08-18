#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define THREAD_NUM 5

pthread_mutex_t
	initMutex,
	mutexArr[THREAD_NUM],
	syncMutexArr[THREAD_NUM];
pthread_cond_t
	initCond,
	syncCond[THREAD_NUM];

void* threadProc(void* param)
{
	int i = *(int*)&param;
	bool init = true;
	while (true)
	{
		if (init)
		{
			init = !init;
			pthread_cond_signal(&initCond);
			if (THREAD_NUM - 1 == i)
				pthread_cond_wait(syncCond + i, syncMutexArr + i);
		}
		else
			pthread_cond_wait(syncCond + i, syncMutexArr + i);
		
		//cout << "mutex[" << i << "]: " << (i + 1) % THREAD_NUM << endl;
		pthread_mutex_lock(&mutexArr[(i + 1) % THREAD_NUM]);
		//cout << "mutex["<< i <<"]: " << (i + 1) % THREAD_NUM << " ok" << endl;
		pthread_mutex_lock(&mutexArr[i]);
		//cout << "mutex[" << i << "]: " << i << " ok" << endl;

		cout << "thread: " << i << " ok" << endl;

		pthread_mutex_unlock(&mutexArr[i]);

		sleep(1);

		pthread_mutex_unlock(&mutexArr[(i + 1) % THREAD_NUM]);
		pthread_cond_signal(syncCond + (i + THREAD_NUM - 1) % THREAD_NUM);
	}

	return NULL;
}

int main()
{
	pthread_t threadArr[THREAD_NUM];

	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_mutex_init(&mutexArr[i], NULL);
		pthread_mutex_init(&syncMutexArr[i], NULL);
		pthread_cond_init(&syncCond[i], NULL);
	}
	pthread_mutex_init(&initMutex, NULL);
	pthread_cond_init(&initCond, NULL);
	pthread_mutex_lock(&mutexArr[0]);
	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_create(threadArr + i, NULL, threadProc, (void*)i);
		pthread_cond_wait(&initCond, &initMutex);
	}
	pthread_mutex_unlock(&mutexArr[0]);
	pthread_mutex_destroy(&initMutex);
	pthread_cond_destroy(&initCond);

	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_join(threadArr[i], NULL);
	}
	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_mutex_destroy(&mutexArr[i]);
		pthread_mutex_destroy(&syncMutexArr[i]);
		pthread_cond_destroy(&syncCond[i]);
	}


	return 0;
}