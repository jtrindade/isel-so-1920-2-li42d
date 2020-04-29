#include <stdint.h>

#define STACK_SIZE (8*4096)

typedef struct uthread {
	uint64_t sp; // fixed at offset 0 (do not move) [see ctxsw.s]
	void * stack;
} UTHREAD, *PUTHREAD;

void context_switch(PUTHREAD currThread, PUTHREAD nextThread);
