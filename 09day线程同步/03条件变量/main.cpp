#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct Node {
	int data;
	Node* next;
};

Node* head;
pthread_cond_t cond;
pthread_mutex_t mutex;

void* productor(void*) {
	while (true) {
		Node* next = (Node*)malloc(sizeof(Node));
		next->next = NULL;
		next->data = rand() % 1000;

		pthread_mutex_lock(&mutex);

		next->next = head;
		head = next;

		cout << "productor: " << head->data << endl;

		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);

		sleep(rand() % 3);
	}

	return NULL;
}


void* customer(void* param) {

	while (true) {
		pthread_mutex_lock(&mutex);

		if (NULL == head)
			pthread_cond_wait(&cond, &mutex);

		Node* temp = head;
		head = head->next;
		cout << "customer" << (char*)param <<": " << temp->data << endl;
		free(temp);

		pthread_mutex_unlock(&mutex);

		sleep(rand() % 6);
	}


	return NULL;
}


int main() {
	srand(time(NULL));

	pthread_t prod, cust1, cust2;

	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&prod, NULL, productor, NULL);
	pthread_create(&cust1, NULL, customer, (void *)"1");
	pthread_create(&cust2, NULL, customer, (void *)"2");

	pthread_join(prod, NULL);
	pthread_join(cust1, NULL);
	pthread_join(cust2, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	return 0;
}