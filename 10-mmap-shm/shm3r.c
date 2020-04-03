#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main() {
	
	key_t key = ftok("texto.txt", 88);
	
	int shmid = shmget(key, 4096, 0666|IPC_CREAT);
	
	void * ptr = shmat(shmid, NULL, 0);

	puts(ptr);
	
	shmdt(ptr);
	
	shmctl(shmid, IPC_RMID, 0);
	
	return 0;
}
