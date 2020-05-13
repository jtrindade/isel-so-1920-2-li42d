#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 24
#define INDIVIDUAL_COUNT 10000

pthread_mutex_t lock;
int global_counter = 0;

void * incrementer(void * ptr) {
	for (int i = 0; i < INDIVIDUAL_COUNT; ++i) {
		pthread_mutex_lock(&lock);
		++global_counter;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main() {

	pthread_mutex_init(&lock, NULL);
	
	pthread_t threads[NTHREADS];
	
	for (int i = 0; i < NTHREADS; ++i) {
		pthread_create(&threads[i], NULL, incrementer, NULL);
	}

	printf(":: waiting... ::\n");
	
	for (int i = 0; i < NTHREADS; ++i) {
		pthread_join(threads[i], NULL);
	}

	printf(":: DONE ::\n");
	
	printf("Expected result: %d\n", NTHREADS * INDIVIDUAL_COUNT);
	printf("Actual   result: %d\n", global_counter);

	pthread_mutex_destroy(&lock);

	return 0;
}