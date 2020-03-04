#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Process: %d\n", getpid());
	printf("Parent:  %d\n", getppid());

	printf("MESSAGE FROM PARENT");
	sleep(10);

	pid_t pid = fork();

	puts("");
	if (pid == 0) {
		printf("Child process: %d\n", getpid());
		printf("Child parent:  %d\n", getppid());
	} else {
		printf("Parent process: %d\n", getpid());
		printf("Parent parent:  %d\n", getppid());
		waitpid(pid, NULL, 0);
	}
	return 0;
}

