#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int res = write(3, "HELLO, WORLD!\n", 14);
	if (res == -1) {
		perror("write error: ");
		exit(1);
	} else {
		fprintf(stderr, "res = %d\n", res);
	}
	return 0;
}
