#include <stdio.h>
#include <unistd.h>
#include "tpool.h"

// execute several print_msg tasks
void print_msg(void * ptr) {
	const char * msg = (const char *)ptr;
	sleep(2);
	puts(msg);
}

int main() {
	tpool_t tpool;
	
	tp_init(&tpool, 3);
	
	tp_submit(&tpool, print_msg, "msg01");
	tp_submit(&tpool, print_msg, "msg02");
	tp_submit(&tpool, print_msg, "msg03");
	tp_submit(&tpool, print_msg, "msg04");
	tp_submit(&tpool, print_msg, "msg05");
	tp_submit(&tpool, print_msg, "msg06");
	
	tp_stop(&tpool, true);
	
	tp_destroy(&tpool);
	return 0;
}