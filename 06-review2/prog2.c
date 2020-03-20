#include <stdlib.h>
#include <stdio.h>

const int a = 9;

char isel[] = { 'I', 'S', 'E', 'L', '\0' };

const char * str = "ISEL";

char * str1 = isel;                // non-const pointer to non-const chars
char const * str2  = "ISEL";       // non-const pointer to const chars
const char * str2x = "ISEL";       // non-const pointer to const chars
char * const str3 = isel;          // const pointer to non-const chars
char const * const str4  = "ISEL"; // const pointer to const chars

int b = 7;

const int z = 99;

int main() {
	int c = 2;
	void * ptr = malloc(1);
	
	printf("[.rodata] %p\n", &a);
	printf("[.rodata] %p\n", &z);
	printf("[.data] %p\n", &b);
	printf("[local] %p\n", &c);
	printf("[local] %p\n", &ptr);
	printf("[dynamic] %p\n", ptr);
	printf("[function] %p\n", main);
	
	free(ptr);
	return 0;
}
