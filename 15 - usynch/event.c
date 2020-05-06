#include <stdlib.h>

#include "usynch.h"
#include "uthread_internal.h"

typedef struct wait_block {
	LIST_ENTRY node;
	PUTHREAD thread;
} WAIT_BLOCK, *PWAIT_BLOCK;

void ut_event_init(PEVENT event) {
	event->signaled = false;
	initializeListHead(&(event->waiters));
}

void ut_event_wait(PEVENT event) {
	if (!event->signaled) {
		
		WAIT_BLOCK wait_block;
		wait_block.thread = ut_self();
		insertTailList(&(event->waiters), &(wait_block.node));
		
		ut_deactivate();
	}
}

void ut_event_signal_all(PEVENT event) {
	event->signaled = true;
	while (!isListEmpty(&(event->waiters))) {
		PLIST_ENTRY entry = removeHeadList(&(event->waiters));
		PWAIT_BLOCK wait_block = container_of(entry, WAIT_BLOCK, node);
		
		ut_activate(wait_block->thread);
	}
}
