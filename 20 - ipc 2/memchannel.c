#include <string.h>

#include "memchannel.h"
#include "shmem.h"

#define SEM_SHARED 1

#define offsetof(FIELD, TYPE) ((size_t)&(((TYPE *)0)->FIELD))

memch_t * mc_create(size_t elem_size, size_t capacity, const char * name) {
	size_t data_size = elem_size * capacity;
	size_t mc_size = sizeof (memch_t) + data_size;   // offsetof(data, memch_t) + data_size
	
	memch_t * mc = (memch_t *)shmem_create(name, mc_size);
	if (!mc) {
		return NULL;
	}

	mc->elem_size = elem_size;
	mc->capacity = capacity;
	mc->mc_size = mc_size;
	
	strncpy(mc->name, name, MEMCH_MAX_NAME_LEN);
	mc->name[MEMCH_MAX_NAME_LEN - 1] = 0;
	
	// int sem_init(sem_t *sem, int pshared, unsigned int value);
	sem_init(&(mc->has_items), SEM_SHARED, 0);
	sem_init(&(mc->has_space), SEM_SHARED, capacity);

	// ...
	
	return mc;
}

void mc_destroy(memch_t * mc) {
	char name[MEMCH_MAX_NAME_LEN];
	strcpy(name, mc->name);
	
	sem_destroy(&(mc->has_items));
	sem_destroy(&(mc->has_space));
	
	shmem_destroy(name, mc, mc->mc_size);
}

memch_t * mc_open(const char * name) {
	return (memch_t *)shmem_open(name, NULL);
}

void mc_close(memch_t * mc) {
	shmem_close(mc, mc->mc_size);
}

void mc_put(memch_t * mc, MC_IN  void * item) {
	sem_wait(&(mc->has_space));
	long iput = atomic_fetch_add(&(mc->iput), 1) % mc->capacity;
	memcpy(mc->data + iput * mc->elem_size, item, mc->elem_size);
	sem_post(&(mc->has_items));
}

void mc_get(memch_t * mc, MC_OUT void * item) {
	sem_wait(&(mc->has_items));
	long iget = atomic_fetch_add(&(mc->iget), 1) % mc->capacity;
	memcpy(item, mc->data + iget * mc->elem_size, mc->elem_size);
	sem_post(&(mc->has_space));
}
