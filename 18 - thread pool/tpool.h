#pragma once

#include <stdlib.h>
#include <pthread.h>
#include "queue.h"

typedef void (*func_t)(void * arg);

typedef struct tpool {
	size_t nthreads;
	pthread_t * threads;
	queue_t work_queue;
} tpool_t;

void tp_init(tpool_t * tpool, size_t nthreads);

void tp_destroy(tpool_t * tpool);

void tp_submit(tpool_t * tpool, func_t func, void * arg);
