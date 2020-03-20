#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
	for (int i = 1; i < argc; ++i) {
		int fd = open(argv[i], O_CREAT|O_RDWR, 0666);
		printf("open: %d\n", fd);
	}
	for (;;) {
		sleep(1);
	}
}
