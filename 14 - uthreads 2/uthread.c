#include <stdint.h>
#include <stdlib.h>

#include "list.h"

#define STACK_SIZE (8*4096)

typedef struct uthread_context {
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t rbx;
	uint64_t rbp;
	void (*ret_addr)();
} UTHREAD_CONTEXT, *PUTHREAD_CONTEXT;

typedef struct uthread {
	uint64_t   sp; // fixed at offset 0 (do not move) [see ctxsw.s]
	void *     stack;
	LIST_ENTRY node;
	void     (*start_routine)(void *);
	void *     argument;
} UTHREAD, *PUTHREAD;

static unsigned int number_of_threads;

static LIST_ENTRY ready_queue;

PUTHREAD running_thread;

void context_switch(PUTHREAD currThread, PUTHREAD nextThread);

static void internal_start() {
	// call thread function with argument
	running_thread->start_routine(running_thread->argument);
	
	// cleanup thread
	ut_exit();
}

void ut_init() {
	number_of_threads = 0;
	initializeHeadList(&ready_queue);
}

void ut_end() {
	// nothing to do
}

void ut_run() {
	
}


void ut_create(void (*start_routine) (void *), void *arg) {
	
	PUTHREAD thread = (PUTHREAD)malloc(sizeof (UTHREAD));
	thread->stack = malloc(STACK_SIZE);
	
	thread->start_routine = start_routine;
	thread->argument = arg;
	
	PUTHREAD_CONTEXT context = (PUTHREAD_CONTEXT)
		(
			(char *)thread->stack
			+ STACK_SIZE
			- sizeof(uint64_t) * 5
			- sizeof(UTHREAD_CONTEXT)
		);
	
	context->r15 = 0x5555555555555555;
	context->r14 = 0x4444444444444444;
	context->r13 = 0x3333333333333333;
	context->r12 = 0x2222222222222222;
	context->rbx = 0x1111111111111111;
	context->rbp = 0x0000000000000000;
	
	context->ret_addr = internal_start;
	
	thread->sp = (uint64_t)context;
	
	number_of_threads += 1;
	insertTailList(&ready_queue, &(thread->node))
}

void ut_yield() {
	
}

void ut_exit() {
	
}
