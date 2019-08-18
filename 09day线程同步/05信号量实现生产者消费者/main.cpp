#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

using namespace std;

struct Node
{
	int data;
	Node* next;
};
Node* head;
sem_t sem;
pthread_mutex_t mutex;

void* productor(void*)
{
	while (true)
	{
		Node* next = (Node*)malloc(sizeof(Node));
		next->data = rand() % 1000;
		
		pthread_mutex_lock(&mutex);

		next->next = head;
		head = next;

		cout << "productor: " << head->data << endl;
		sem_post(&sem);

		pthread_mutex_unlock(&mutex);
		
		sleep(rand() % 3);
	}

	return NULL;
}

void* customer(void* param)
{

	while (true)
	{
		char* str = (char*)param;

		sem_wait(&sem);

		pthread_mutex_lock(&mutex);
	
		Node* temp = head;
		head = head->next;
		cout << "customer" << str << ": " << temp->data << endl;
		free(temp);

		pthread_mutex_unlock(&mutex);

		sleep(rand() % 3);
	}
	


	return NULL;
}

int main()
{
	pthread_t prodrth1, custrth1;

	srand(time(NULL));
	
	sem_init(&sem, 0, 0);
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&prodrth1, NULL, productor, NULL);
	pthread_create(&custrth1, NULL, customer, (void*)"1");

	pthread_join(prodrth1, NULL);
	pthread_join(custrth1, NULL);

	pthread_mutex_destroy(&mutex);
	sem_destroy(&sem);

	return 0;
}