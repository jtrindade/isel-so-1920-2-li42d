#pragma once

#include <pthread.h> 

typedef struct cdlatch {
	pthread_mutex_t lock;
	pthread_cond_t waiters;
	unsigned count;
} cdlatch_t;

void cdlatch_init(cdlatch_t * latch, unsigned count);

void cdlatch_destroy(cdlatch_t * latch);

// blocking
void cdlatch_await(cdlatch_t * latch);

// unblocking
void cdlatch_count_down(cdlatch_t * latch);
