#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Process: %d\n", getpid());
	printf("Parent:  %d\n", getppid());

	pid_t pid = fork();

	if (pid == 0) {
		printf("Child process: %d\n", getpid());
		printf("Child parent:  %d\n", getppid());
		exit(88);
	} else {
		int res;
		printf("Parent process: %d\n", getpid());
		printf("Parent parent:  %d\n", getppid());
		getchar();
		waitpid(pid, &res, 0);
		if (WIFEXITED(res)) {
			printf("Child result: %d\n", WEXITSTATUS(res));
		}
		getchar();
	}

	return 0;
}

