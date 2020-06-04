#pragma once

#include <pthread.h>
#include "list.h"

typedef struct queue {
	pthread_mutex_t lock;
	pthread_cond_t  has_items;
	LIST_ENTRY      list;
	unsigned        size;
} queue_t;

void queue_init(queue_t * queue);

void queue_destroy(queue_t * queue);

void queue_put(queue_t * queue, void * item);

void * queue_get(queue_t * queue);
