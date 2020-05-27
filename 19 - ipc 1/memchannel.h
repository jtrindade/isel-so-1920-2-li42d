#pragma once

#include <stdlib.h>
#include <stdatomic.h>
#include <semaphore.h>

#define MEMCH_MAX_NAME_LEN 128

typedef unsigned char byte;

typedef struct memch {
	size_t elem_size;
	size_t capacity;
	
	char name[MEMCH_MAX_NAME_LEN];
	
	sem_t has_items;
	sem_t has_space;
	
	atomic_long iput;
	atomic_long iget;
	
	size_t mc_size;
	byte data[1];
} memch_t;

////////////////////////////////////////////////
//
// Operations for programs that create and
// destroy memory channels.
//

memch_t * mc_create(size_t elem_size, size_t capacity, const char * name);

void mc_destroy(memch_t * mc);

////////////////////////////////////////////////
//
// Operations for programs that attach to and
// dettach from existing memory channels.
//

memch_t * mc_open(const char * name);

void mc_close(memch_t * mc);

////////////////////////////////////////////////
//
// Operations for reading and writing in
// existing memory channels.
//

#define MC_IN
#define MC_OUT

void mc_put(memch_t * mc, MC_IN  void * item);

void mc_get(memch_t * mc, MC_OUT void * item);
