#include <stdio.h>
#include <unistd.h>
#include "tpool.h"

// execute several print_msg tasks
void print_msg(const char * msg) {
	puts(msg);
}

int main() {
	tpool_t tpool;
	
	tp_init(&tpool, 3);
	
	tp_submit(&tpool, ???);
	tp_submit(&tpool, ???);
	tp_submit(&tpool, ???);
	tp_submit(&tpool, ???);
	tp_submit(&tpool, ???);
	tp_submit(&tpool, ???);
	
	sleep(8); // inapropriado; falta funcao no thread pool para concluir
	
	return 0;
}