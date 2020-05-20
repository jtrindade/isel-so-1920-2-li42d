#include <stdio.h>

#include <limits.h>
#include <assert.h>
#include "chrono.h"

#define NITERS 50
#define NVALS 50000

int vals[NVALS];

static void init_vals() {
	for(int i = 0; i < NVALS; ++i)
		vals[i] = 1;
}

long seq_adder(int vals[], size_t nvals) {
	long total = 0;
	for (size_t i = 0; i < nvals; ++i)
		total += vals[i];
	return total;
}

void test(char *name,
		long (*sum_func)(int vals[], size_t nvals), 
		int vals[], 
		int nvals, 
		long expected) {
	
	unsigned long micros, less_micros = ULONG_MAX;
	long res;
	for(int i = 0; i < NITERS; ++i) {
		chrono_t chrono = chrono_start();
		{
			res = sum_func(vals, nvals);
		}
		micros = chrono_micros(chrono);

		if (micros < less_micros) 
			less_micros = micros;

		assert(expected == res);
	}
	
	printf("%s gives a result of %ld in %lu micros.\n", 
			name, res, less_micros);
}

int main() {
	init_vals();
	 
	test("sequential adder", seq_adder, vals, NVALS, NVALS);
	
	return 0;
}
