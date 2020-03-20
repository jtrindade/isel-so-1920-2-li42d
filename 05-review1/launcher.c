#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 256

char cmd[BUFSIZE] = { '.', '/' };

int main() {
	for (;;) {
		printf("> ");
		fgets(&cmd[2], BUFSIZE-2, stdin);
		char * nl = strchr(&cmd[2], '\n');
		if (nl) *nl = 0;
		
		if (strcmp(cmd+2, "exit") == 0) {
			break;
		}
		
		pid_t pid = fork();
		if (pid == 0) {
			execlp(cmd, cmd+2, NULL);
			perror("exec failed");
			exit(1);
		} else {
			int status;
			waitpid(pid, &status, 0);
			if (WIFEXITED(status)) {
				printf("res: %d\n", WEXITSTATUS(status));
			} else {
				printf("end\n");
			}
		}
	}
	return 0;
}
