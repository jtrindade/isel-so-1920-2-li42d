#include <stdlib.h>

#include "usynch.h"
#include "uthread_internal.h"

typedef struct sem_wait_block {
	LIST_ENTRY node;
	PUTHREAD thread;
	unsigned count;
} SEM_WAIT_BLOCK, *PSEM_WAIT_BLOCK;

void ut_sem_init(PSEMAPHORE sem, unsigned initial_count, unsigned limit) {
	sem->limit = limit;
	sem->counter = initial_count;
	initializeListHead(&(sem->waiters));
}

void ut_sem_wait(PSEMAPHORE sem, unsigned count) {
	if (sem->counter >= count && isListEmpty(&(sem->waiters))) {
		sem->counter -= count;
	} else {
		SEM_WAIT_BLOCK wait_block;
		wait_block.thread = ut_self();
		wait_block.count = count;
		insertTailList(&(sem->waiters), &(wait_block.node));
		
		ut_deactivate();
	}
}

void ut_sem_post(PSEMAPHORE sem, unsigned count) {
	sem->counter += count;
	
	if (sem->counter > sem->limit) {
		sem->counter = sem->limit;
	}
	
	while (!isListEmpty(&(sem->waiters))) {
		PLIST_ENTRY first_waiter_entry = sem->waiters.flink;
		PSEM_WAIT_BLOCK first_waiter = container_of(first_waiter_entry, SEM_WAIT_BLOCK, node);
		
		if (sem->counter < first_waiter->count) {
			return;
		}
		
		sem->counter -= first_waiter->count;
		removeHeadList(&(sem->waiters));
		
		ut_activate(first_waiter->thread);
	}
}
