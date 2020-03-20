#include <stdio.h>

const int x = 22;

int y = 33;

void func() {
	int z = 44;
	
	printf("[libx] [.rodata] %p\n", &x);
	printf("[libx] [.data] %p\n", &y);
	printf("[libx] [local] %p\n", &z);
	printf("[libx] [function] %p\n", func);
}
