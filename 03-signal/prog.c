#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Running...\n");
	for (;;) {
		sleep(1);
	}
	printf("END\n");
	return 0;
}
