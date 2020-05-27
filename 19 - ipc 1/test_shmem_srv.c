#include <stdlib.h>
#include <stdio.h>
#include "shmem.h"

#define SHMEM_NAME "pt.isel.leic.so.shmem.test"
#define SHMEM_SIZE 4096

int main() {
	
	puts(":: STARTED ::");
	
	printf("Creating shared memory with: name=\"%s\" size=%d\n", SHMEM_NAME, SHMEM_SIZE);
	void * mem = shmem_create(SHMEM_NAME, SHMEM_SIZE);
	if (!mem) {
		exit(1);
	}

	int val;
	do {
		puts("READY: press ENTER to read a value...");
		getchar();
		
		val = *(int *)mem;
		
		printf("val: %d\n", val);

	} while (val);

	puts("DONE: press ENTER to exit...");
	getchar();

	shmem_destroy(SHMEM_NAME, mem, SHMEM_SIZE);
	
	puts(":: END ::");
	return 0;
}
