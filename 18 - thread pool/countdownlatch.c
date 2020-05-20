#include "countdownlatch.h"

void cdlatch_init(cdlatch_t * latch, unsigned count) {
	pthread_mutex_init(&(latch->lock), NULL);
	pthread_cond_init(&(latch->waiters), NULL);
	latch->count = count;
}

void cdlatch_destroy(cdlatch_t * latch) {
	pthread_cond_destroy(&(latch->waiters));
	pthread_mutex_destroy(&(latch->lock));
}

// blocking
void cdlatch_await(cdlatch_t * latch) {
	pthread_mutex_lock(&(latch->lock));
	{
		while (latch->count > 0) {
			pthread_cond_wait(&(latch->waiters), &(latch->lock));
		}
	}
	pthread_mutex_unlock(&(latch->lock));
}

// unblocking
void cdlatch_count_down(cdlatch_t * latch) {
	pthread_mutex_lock(&(latch->lock));
	{
		latch->count -= 1;
		pthread_cond_broadcast(&(latch->waiters));
	}
	pthread_mutex_unlock(&(latch->lock));
}
