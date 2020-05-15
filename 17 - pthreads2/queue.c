#include "queue.h"

#include <stdlib.h>

typedef struct queue_node {
	int value;
	LIST_ENTRY entry;
} QUEUE_NODE, *PQUEUE_NODE;

void queue_init(PQUEUE queue) {
	pthread_mutex_init(&(queue->lock), NULL);
	pthread_cond_init(&(queue->waiters), NULL);
	initializeListHead(&(queue->head));
	queue->size = 0;
}

void queue_cleanup(PQUEUE queue) {
	pthread_cond_destroy(&(queue->waiters));
	pthread_mutex_destroy(&(queue->lock));
}

void queue_offer(PQUEUE queue, int val) {
	PQUEUE_NODE node = (PQUEUE_NODE)malloc(sizeof (QUEUE_NODE));
	node->value = val;
	pthread_mutex_lock(&(queue->lock));
	{
		insertTailList(&(queue->head), &(node->entry));
		queue->size += 1;
		pthread_cond_signal(&(queue->waiters));
	}
	pthread_mutex_unlock(&(queue->lock));
}

int queue_take(PQUEUE queue) {
	PLIST_ENTRY pentry = NULL;
	pthread_mutex_lock(&(queue->lock));
	{
		while (queue->size == 0) {
			// atomically[ unlock mutex ; wait for signal ] ; relock mutex
			pthread_cond_wait(&(queue->waiters), &(queue->lock));
		}
		queue->size -= 1;
		pentry = removeHeadList(&(queue->head));
	}
	pthread_mutex_unlock(&(queue->lock));
	if (pentry != NULL) {
		PQUEUE_NODE node = container_of(pentry, QUEUE_NODE, entry);
		int val = node->value;
		free(node);
		return val;
	}
	// Should never occur!
	return -1;
}
