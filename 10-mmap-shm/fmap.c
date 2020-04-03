#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]) {
	int fd = open(argv[1], O_RDWR);
	
	void * ptr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	puts(ptr);
	if (argc >= 3) {
		strcpy(ptr, argv[2]);
	}
	
	munmap(ptr, 4096);
	close(fd);

	return 0;
}