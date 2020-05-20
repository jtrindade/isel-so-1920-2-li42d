#pragma once

#include <stdlib.h>

typedef struct tpool {
	size_t nthreads;
	// ...
} tpool_t;

void tp_init(tpool_t * tpool, size_t nthreads);

void tp_destroy(tpool_t * tpool);

void tp_submit(tpool_t * tpool, ???);
