#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "countdownlatch.h"

CDLATCH latch;

void * waiter(void * ptr) {
	const char * name = (const char *)ptr;
	printf("%s waiting...\n", name);
	cdlatch_await(&latch);
	printf("%s released...\n", name);
	return NULL;
}

int main() {
	cdlatch_init(&latch, 3);
	
	pthread_t threads[5];
	char names[5][3];
	
	for (int i = 0; i < 5; ++i) {
		strcpy(names[i], "T0");
		names[i][1] += i;
		pthread_create(&threads[i], NULL, waiter, names[i]);
	}
	
	printf(":: working... ::\n");
	
	for (int i = 0; i < 3; ++i) {
		sleep(2);
		printf(":: count down ::\n");
		cdlatch_count_down(&latch);
	}

	for (int i = 0; i < 5; ++i) {
		pthread_join(threads[i], NULL);
	}
	
	printf(":: DONE ::\n");
	
	cdlatch_cleanup(&latch);
	return 0;
}
