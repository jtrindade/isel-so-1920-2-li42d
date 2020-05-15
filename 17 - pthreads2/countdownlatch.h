#pragma once

#include <pthread.h> 

typedef struct cdlatch {
	pthread_mutex_t lock;
	pthread_cond_t waiters;
	unsigned count;
} CDLATCH, *PCDLATCH;

void cdlatch_init(PCDLATCH latch, unsigned count);

void cdlatch_cleanup(PCDLATCH latch);

// blocking
void cdlatch_await(PCDLATCH latch);

// unblocking
void cdlatch_count_down(PCDLATCH latch);
