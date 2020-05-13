#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void * print_message(void * ptr) {
	const char * msg = (const char *)ptr;
	for (int i = 0; i < 8; ++i) {
		printf("%s\n", msg);
		sleep(1);
	}
	return NULL;
}

int main() {
	
	pthread_t thread1, thread2;
	
	pthread_create(&thread1, NULL, print_message, "Thread 1");
	pthread_create(&thread2, NULL, print_message, "Thread 2");
	
	printf(":: waiting... ::\n");
	
	pthread_join(thread2, NULL);
	pthread_join(thread1, NULL);

	printf(":: DONE ::\n");
	return 0;
}