#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int clone(int (*fn)(void *), void * stack, int flags, void * arg, ...);

#define STACK_SIZE (32*1024)

int num = 6;

int child_func(void * arg) {
	printf("child pid: %d\n", getpid());
	num += 2;
	printf("child num: %d\n", num);
	return num;
}

int main() {
	int child_id;

	printf("parent pid: %d\n", getpid());
	
	// Flags = 0 : cria um novo espaço de endereçamento independente
	child_id = clone(child_func, malloc(STACK_SIZE) + STACK_SIZE, 0, NULL);
	// Flags = CLONE_VM : cria fio de execução no mesmo espaço de endereçamento
	// child_id = clone(child_func, malloc(STACK_SIZE) + STACK_SIZE, CLONE_VM, NULL);

	if (child_id == -1) {
		perror("failed to clone");
		exit(1);
	}
	
	if (waitpid(-1, NULL, __WCLONE) == -1) {
		perror("failed to wait");
		exit(2);
	}
	
	printf("parent num: %d\n", num);
	return 0;
}
