#include <stdio.h>

#include <limits.h>
#include <assert.h>
#include "chrono.h"

#include "tpool.h"
#include "countdownlatch.h"

#define NTHREADS 4
#define NITERS 50
#define NVALS 5000000

tpool_t tpool;

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

typedef struct sum_task {
	cdlatch_t * latch;
	int * pini;
	int * pend;
	long result;
} sum_task_t;

void sum_task_func1(void * ptr) {
	sum_task_t * sum_task = (sum_task_t *)ptr;
	long total = 0;
	for (int * p = sum_task->pini; p < sum_task->pend; p += NTHREADS) {
		total += *p;
	}
	sum_task->result = total;
	cdlatch_count_down(sum_task->latch);
}

long par_adder1(int vals[], size_t nvals) {
	cdlatch_t latch;
	cdlatch_init(&latch, NTHREADS);
	
	sum_task_t sum_tasks[NTHREADS];	
	for (int i = 0; i < NTHREADS; ++i) {
		sum_tasks[i].latch = &latch;
		sum_tasks[i].pini = &vals[i];
		sum_tasks[i].pend = &vals[nvals];
		
		tp_submit(&tpool, sum_task_func1, &sum_tasks[i]);
	}
	
	cdlatch_await(&latch);
	
	long total = 0;
	for (int i = 0; i < NTHREADS; ++i) {
		total += sum_tasks[i].result;
	}
	
	return total;
}

/*
typedef struct sum_task {
	cdlatch_t * latch;
	int * pini;
	int * pend;
	long result;
} sum_task_t;
*/

void sum_task_func2(void * ptr) {
	sum_task_t * sum_task = (sum_task_t *)ptr;
	long total = 0;
	for (int * p = sum_task->pini; p < sum_task->pend; ++p) {
		total += *p;
	}
	sum_task->result = total;
	cdlatch_count_down(sum_task->latch);
}

long par_adder2(int vals[], size_t nvals) {
	cdlatch_t latch;
	cdlatch_init(&latch, NTHREADS);
	
	int region_size = (nvals + (NTHREADS - 1)) / NTHREADS;
	
	sum_task_t sum_tasks[NTHREADS];
	for (int i = 0; i < NTHREADS; ++i) {
		int * pini = &vals[i * region_size];
		int * pend = (pini + region_size) < &vals[nvals] ?
			(pini + region_size) :
			&vals[nvals];
		
		sum_tasks[i].latch = &latch;
		sum_tasks[i].pini = pini;
		sum_tasks[i].pend = pend;

		tp_submit(&tpool, sum_task_func2, &sum_tasks[i]);
	}
	
	cdlatch_await(&latch);
	
	long total = 0;
	for (int i = 0; i < NTHREADS; ++i) {
		total += sum_tasks[i].result;
	}
	
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
	tp_init(&tpool, NTHREADS);
	
	init_vals();
	 
	test("sequential adder", seq_adder,  vals, NVALS, NVALS);
	test("parallel#1 adder", par_adder1, vals, NVALS, NVALS);
	test("parallel#2 adder", par_adder2, vals, NVALS, NVALS);
	
	// tp_destroy(&tpool);
	return 0;
}
