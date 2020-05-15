#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include "list.h"

typedef struct queue {
	pthread_mutex_t lock;
	pthread_cond_t waiters;
	LIST_ENTRY head;
	unsigned size;
} QUEUE, *PQUEUE;

void queue_init(PQUEUE queue);

void queue_cleanup(PQUEUE queue);

void queue_offer(PQUEUE queue, int val);

int queue_take(PQUEUE queue);

#endif // QUEUE_H
