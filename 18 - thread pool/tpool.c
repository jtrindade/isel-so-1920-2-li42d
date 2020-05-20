#include "tpool.h"

typedef struct workitem {
	func_t func;
	void * arg;
} workitem_t;

static void * worker_func(void * ptr) {
	tpool_t * tpool = (tpool_t *)ptr;
	for (;;) {
		workitem_t * wi = (workitem_t *)queue_get(&(tpool->work_queue));
		func_t func = wi->func;
		void * arg = wi->arg;
		free(wi);
		
		func(arg);
	}
	return NULL;
}

void tp_init(tpool_t * tpool, size_t nthreads) {
	queue_init(&(tpool->work_queue));
	tpool->nthreads = nthreads;
	tpool->threads = (pthread_t *)malloc(nthreads * sizeof (pthread_t));
	for (size_t i = 0; i < nthreads; ++i) {
		pthread_create(&(tpool->threads[i]), NULL, worker_func, tpool);
	}
}

void tp_destroy(tpool_t * tpool) {
	// ...
	free(tpool->threads);
	queue_destroy(&(tpool->work_queue));
}

void tp_submit(tpool_t * tpool, func_t func, void * arg) {
	workitem_t * wi = (workitem_t *)malloc(sizeof (workitem_t));
	wi->func = func;
	wi->arg = arg;	
	queue_put(&(tpool->work_queue), wi);
}
