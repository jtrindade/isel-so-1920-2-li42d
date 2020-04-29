#include <stdio.h>

#include "uthread.h"

void f1(void * arg) {
	const char * str = (const char *)arg;
	printf("%s: step 1\n", str);
	ut_yield();
	printf("%s: step 2\n", str);
	ut_yield();
	printf("%s: step 3\n", str);
}

void f2(void * arg) {
	printf("hello, world!\n");
}

void f3(void * arg) {
	const char * str = (const char *)arg;
	printf("%s: step 1\n", str);
	ut_yield();
	printf("%s: step 2\n", str);
	ut_yield();
	printf("%s: step 3\n", str);
}

int main() {
	ut_init();

	ut_create(f1, "t1");
	ut_create(f2, NULL);
	ut_create(f3, "t3");

	printf(":: START ::\n");
	ut_run();
	printf(":: END ::\n");
	
	ut_end();
	return 0;
}
