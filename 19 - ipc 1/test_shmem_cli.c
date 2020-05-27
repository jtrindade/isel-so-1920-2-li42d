#include <stdlib.h>
#include <stdio.h>
#include "shmem.h"

#define SHMEM_NAME "pt.isel.leic.so.shmem.test"

int main(int argc, char * argv[]) {
	
	size_t size;
	void * mem = shmem_open(SHMEM_NAME, &size);
	if (!mem) {
		exit(1);
	}
	printf("Attached to shared memory: name=\"%s\" size=%ld\n", SHMEM_NAME, size);
	
	int val = (argc == 1) ? 0 : atoi(argv[1]);
	
	printf("READY: press ENTER to write the value %d\n", val);
	getchar();

	*(int *)mem = val;
	
	shmem_close(mem, size);
	return 0;
}
