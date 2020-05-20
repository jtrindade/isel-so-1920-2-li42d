#include "tpool.h"

void tp_init(tpool_t * tpool, size_t nthreads) {
	tpool->nthreads = nthreads;
	// ...
}

void tp_destroy(tpool_t * tpool) {
	// ...
}

void tp_submit(tpool_t * tpool, ???) {
	// ...
}
