#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/syscall.h>
#ifdef SYS_gettid
#define gettid() ((pid_t)syscall(SYS_gettid))
#else
#error SYS_gettid undefined
#endif

void * print_message(void * ptr) {
	const char * msg = (const char *)ptr;
	for (int i = 0; i < 8; ++i) {
		printf("P%d T%d: %s\n", getpid(), gettid(), msg);
		sleep(1);
	}
	long retval = strlen(msg) >= 8 ? msg[7] : 0;
	return (void *)retval;
}

int main() {
	
	pthread_t thread1, thread2;
	intptr_t res1, res2;
	
	pthread_create(&thread1, NULL, print_message, "Thread 1");
	pthread_create(&thread2, NULL, print_message, "Thread 2");
	
	printf("P%d T%d: :: waiting... ::\n", getpid(), gettid());
	
	pthread_join(thread2, (void**)&res2);
	pthread_join(thread1, (void**)&res1);

	printf("P%d T%d: :: DONE ::\n", getpid(), gettid());
	
	printf("res1: %ld\n", res1);
	printf("res2: %ld\n", res2);

	return 0;
}
