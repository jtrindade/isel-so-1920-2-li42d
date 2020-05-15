#include <stdio.h>
#include <unistd.h>

#include "queue.h"

#define NTHREADS 30
#define INDIVIDUAL_COUNT 10000

QUEUE queue;

void * insert(void * ptr) {
	sleep(10);
	int base = (long)ptr;
	for (int i = 0; i < INDIVIDUAL_COUNT; ++i) {
		queue_offer(&queue, base + i);
	}
	return NULL;
}

int main() {
	
	pthread_t threads[NTHREADS];
	
	queue_init(&queue);

	printf(":: starting... ::\n");
	
	for (int i = 0; i < NTHREADS; ++i) {
		pthread_create(&threads[i], NULL, insert, (void*)(long)((i + 1) * INDIVIDUAL_COUNT));
	}

	/*
	printf(":: waiting... ::\n");

	for (int i = 0; i < NTHREADS; ++i) {
		pthread_join(threads[i], NULL);
	}
	*/

	printf(":: taking... ::\n");
	
	for (int i = 0; i < NTHREADS*INDIVIDUAL_COUNT; ++i) {
		printf("%d\n", queue_take(&queue));
	}

	queue_cleanup(&queue);
	
	return 0;
}
