#pragma once 

#include <stdlib.h>

////////////////////////////////////////////////
//
// Operations for programs that create and
// destroy shared memory areas.
//

void * shmem_create(const char *name, size_t size);

void shmem_destroy(const char * name, void *base, size_t size);

////////////////////////////////////////////////
//
// Operations for programs that attach to and
// dettach from existing shared memory areas.
//

void * shmem_open(const char *name, size_t *psize);

void shmem_close(void *base, size_t size);

