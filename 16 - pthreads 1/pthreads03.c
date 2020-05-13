#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 24
#define INDIVIDUAL_COUNT 10000

int global_counter = 0;

void * incrementer(void * ptr) {
	for (int i = 0; i < INDIVIDUAL_COUNT; ++i) {
		//++global_counter;
		__sync_fetch_and_add(&global_counter, 1);
	}
	return NULL;
}

int main() {
	
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

	return 0;
}