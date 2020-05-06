#ifndef UTHREAD_INTERNAL_H
#define UTHREAD_INTERNAL_H

#include <stdint.h>

typedef struct uthread {
	uint64_t   sp; // fixed at offset 0 (do not move) [see ctxsw.s]
	void *     stack;
	LIST_ENTRY node;
	void     (*start_routine)(void *);
	void *     argument;
} UTHREAD, *PUTHREAD;

PUTHREAD ut_self();

void ut_deactivate();

void ut_activate(PUTHREAD thread); 

#endif // UTHREAD_INTERNAL_H
