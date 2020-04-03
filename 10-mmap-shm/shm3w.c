#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
	
	key_t key = ftok("texto.txt", 88);
	
	int shmid = shmget(key, 4096, 0666|IPC_CREAT);
	
	void * ptr = shmat(shmid, NULL, 0);
	
	strcpy(ptr, "ISEL - LEIC - PI");
	
	shmdt(ptr);
	
	return 0;
}
