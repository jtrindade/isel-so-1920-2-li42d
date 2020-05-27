#include <stdlib.h>
#include <stdio.h>
#include "memchannel.h"

#define MEMCH_NAME "pt.isel.leic.so.memch.test"

int main(int argc, char * argv[]) {
	
	memch_t * mc = mc_open(MEMCH_NAME);
	if (!mc) {
		exit(1);
	}
	printf("Attached to memory channel: name=\"%s\" size=%ld\n", MEMCH_NAME, mc->mc_size);
	
	int val = (argc == 1) ? 0 : atoi(argv[1]);
	
	printf("READY: press ENTER to write the value %d\n", val);
	getchar();

	mc_put(mc, &val);

	mc_close(mc);
	return 0;
}
