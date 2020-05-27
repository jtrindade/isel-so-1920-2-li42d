#include <stdlib.h>
#include <stdio.h>
#include "memchannel.h"

#define MEMCH_NAME "pt.isel.leic.so.memch.test"
#define MEMCH_ELEMSIZE (sizeof (int))
#define MEMCH_CAPACITY 8

int main() {
	
	puts(":: STARTED ::");
	
	printf("Creating memory channel named \"%s\"\n", MEMCH_NAME);
	memch_t * mc = mc_create(MEMCH_ELEMSIZE, MEMCH_CAPACITY, MEMCH_NAME);
	if (!mc) {
		exit(1);
	}

	int val;
	do {
		puts("READY: waiting for a value...");

		mc_get(mc, &val);
		
		printf("\nval: %d\n\n", val);

	} while (val);

	puts("DONE: destroying...");

	mc_destroy(mc);
	
	puts(":: END ::");
	return 0;
}
