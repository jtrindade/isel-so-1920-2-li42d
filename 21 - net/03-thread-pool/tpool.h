#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"

typedef enum tpool_state {
	TP_RUNNING, TP_FINISHING, TP_STOPPING, TP_STOPPED
} tpool_state_t;

typedef void (*func_t)(void * arg);

typedef struct tpool {
	tpool_state_t state;
	size_t nthreads;
	pthread_t * threads;
	queue_t work_queue;
} tpool_t;

void tp_init(tpool_t * tpool, size_t nthreads);

void tp_stop(tpool_t * tpool, bool finish_all_tasks);

void tp_destroy(tpool_t * tpool);

bool tp_submit(tpool_t * tpool, func_t func, void * arg);
