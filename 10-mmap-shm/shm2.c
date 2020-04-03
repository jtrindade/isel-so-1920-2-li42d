#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	
	void * ptr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, 0, 0);
	if (!ptr) {
		perror("mmap failed");
		exit(1);
	}

	pid_t pid = fork();
	if (pid == 0) {
		strcpy(ptr, "Hello, world!");
	} else {
		waitpid(pid, NULL, 0);
		puts(ptr);
	}

	munmap(ptr, 4096);

	return 0;
}