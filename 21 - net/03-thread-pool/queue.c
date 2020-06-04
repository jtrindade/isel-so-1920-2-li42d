#include "queue.h"

#include <stdlib.h>

typedef struct queue_node {
	void * item;
	LIST_ENTRY entry;
} queue_node_t;

void queue_init(queue_t * queue) {
	pthread_mutex_init(&(queue->lock), NULL);
	pthread_cond_init(&(queue->has_items), NULL);
	initializeListHead(&(queue->list));
	queue->size = 0;
}

void queue_destroy(queue_t * queue) {
	pthread_cond_destroy(&(queue->has_items));
	pthread_mutex_destroy(&(queue->lock));
}

void queue_put(queue_t * queue, void * item) {
	queue_node_t * node = (queue_node_t *)malloc(sizeof (queue_node_t));
	node->item = item;
	pthread_mutex_lock(&(queue->lock));
	{
		insertTailList(&(queue->list), &(node->entry));
		queue->size += 1;
		pthread_cond_signal(&(queue->has_items));
	}
	pthread_mutex_unlock(&(queue->lock));
}

void * queue_get(queue_t * queue) {
	PLIST_ENTRY entry = NULL;

	pthread_mutex_lock(&(queue->lock));
	{
		while (queue->size == 0) {
			pthread_cond_wait(&(queue->has_items), &(queue->lock));
		}
		queue->size -= 1;
		entry = removeHeadList(&(queue->list));
	}
	pthread_mutex_unlock(&(queue->lock));
	
	if (entry != NULL) {
		queue_node_t * node = container_of(entry, queue_node_t, entry);
		void * item = node->item;
		free(node);
		return item;
	}
	
	// cannot occur
	return NULL;
}
