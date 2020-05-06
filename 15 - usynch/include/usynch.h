#ifndef USYNCH_H
#define USYNCH_H

#include <stdbool.h>
#include "list.h"

// Event

typedef struct event {
	bool signaled;
	LIST_ENTRY waiters;
} EVENT, *PEVENT;

void ut_event_init(PEVENT event);

void ut_event_wait(PEVENT event);

void ut_event_signal_all(PEVENT event);


// Semaphore

typedef struct semaphore {
	unsigned limit;
	unsigned counter;
	LIST_ENTRY waiters;
} SEMAPHORE, *PSEMAPHORE;

void ut_sem_init(PSEMAPHORE sem, unsigned initial_count, unsigned limit);

void ut_sem_wait(PSEMAPHORE sem, unsigned count);

void ut_sem_post(PSEMAPHORE sem, unsigned count);

#endif // USYNCH_H
