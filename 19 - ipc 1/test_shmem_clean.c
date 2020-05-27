#include <sys/mman.h>

#define SHMEM_NAME "isel.shmem_test"

int main() {
	
	shm_unlink(SHMEM_NAME);
	
	return 0;
}
