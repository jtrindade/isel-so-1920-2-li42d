#include <stdint.h>
#include <stdlib.h>

#include "list.h"
#include "uthread.h"
#include "uthread_internal.h"

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

static unsigned int number_of_threads;

static LIST_ENTRY ready_queue;

PUTHREAD running_thread;

static PUTHREAD main_thread;

static void internal_start() {
	// call thread function with argument
	running_thread->start_routine(running_thread->argument);

	// cleanup thread
	ut_exit(); // never returns
}

void internal_exit(PUTHREAD currThread, PUTHREAD nextThread);

void context_switch(PUTHREAD currThread, PUTHREAD nextThread);

void cleanup_thread(PUTHREAD thread) {
	free(thread->stack);
	free(thread);
}

__attribute__((always_inline))
static inline PUTHREAD extract_next_ready_thread() {
	if (isListEmpty(&ready_queue)) {
		return main_thread;
	}
	PLIST_ENTRY thread_node = removeHeadList(&ready_queue);
	PUTHREAD next_thread = container_of(thread_node, UTHREAD, node);
	return next_thread;
}

__attribute__((always_inline))
static inline void schedule() {
	PUTHREAD next_thread = extract_next_ready_thread();
	context_switch(running_thread, next_thread);
}

void ut_init() {
	number_of_threads = 0;
	initializeListHead(&ready_queue);
}

void ut_end() {
	// nothing to do
}

void ut_run() {
	UTHREAD thread;
	
	if (isListEmpty(&ready_queue)) {
		return;
	}
	
	main_thread = running_thread = &thread;
	
	schedule();

	main_thread = running_thread = NULL;
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
			- sizeof (uint64_t) * 5
			- sizeof (UTHREAD_CONTEXT)
		);

	context->r15 = 0x5555555555555555;
	context->r14 = 0x4444444444444444;
	context->r13 = 0x3333333333333333;
	context->r12 = 0x2222222222222222;
	context->rbx = 0x1111111111111111;
	context->rbp = 0x0000000000000000; // mandatory for debuggers
	
	context->ret_addr = internal_start;
	
	thread->sp = (uint64_t)context;
	
	number_of_threads += 1;
	insertTailList(&ready_queue, &(thread->node));
}

void ut_exit() {
	number_of_threads -= 1;
	PUTHREAD next_thread = extract_next_ready_thread();
	internal_exit(running_thread, next_thread);
}

void ut_yield() {
	if (!isListEmpty(&ready_queue)) {
		insertTailList(&ready_queue, &(running_thread->node));
		schedule();
	}
}

PUTHREAD ut_self() {
	return running_thread;
}

void ut_deactivate() {
	schedule();
}

void ut_activate(PUTHREAD thread) {
	insertTailList(&ready_queue, &(thread->node));
}
