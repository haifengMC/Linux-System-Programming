#include <pthread.h>
#include <iostream>
#include <unistd.h>

using namespace std;
int num = 0;

pthread_rwlock_t rwlock;

void* threadProc1(void*)
{
	while (true)
	{
		pthread_rwlock_rdlock(&rwlock);

		cout << "threadProc1 read : " << num << endl;

		pthread_rwlock_unlock(&rwlock);

		sleep(1);
	}
	
	return NULL;
}

void* threadProc2(void*)
{
	while (true)
	{
		pthread_rwlock_rdlock(&rwlock);

		cout << "threadProc2 read : " << num << endl;

		pthread_rwlock_unlock(&rwlock);

		sleep(1);
	}

	return NULL;
}

void* threadProc3(void*)
{
	while (true)
	{
		pthread_rwlock_wrlock(&rwlock);

		++num;
		cout << "threadProc3 write : " << num << endl;

		pthread_rwlock_unlock(&rwlock);

		sleep(2);
	}

	return NULL;
}

void* threadProc4(void*)
{
	while (true)
	{
		pthread_rwlock_wrlock(&rwlock);

		++num;
		cout << "threadProc4 write : " << num << endl;

		pthread_rwlock_unlock(&rwlock);

		sleep(2);
	}

	return NULL;
}

int main()
{
	pthread_t pthd1, pthd2, pthd3, pthd4;

	pthread_rwlock_init(&rwlock, NULL);

	pthread_create(&pthd1, NULL, threadProc1, NULL);
	pthread_create(&pthd2, NULL, threadProc2, NULL);
	pthread_create(&pthd3, NULL, threadProc3, NULL);
	pthread_create(&pthd4, NULL, threadProc4, NULL);

	pthread_join(pthd1, NULL);
	pthread_join(pthd2, NULL);
	pthread_join(pthd3, NULL);
	pthread_join(pthd4, NULL);

	pthread_rwlock_destroy(&rwlock);


	return 0;
}