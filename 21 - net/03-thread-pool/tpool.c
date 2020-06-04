#include "tpool.h"
#include <stdio.h>

typedef struct workitem {
	func_t func;
	void * arg;
} workitem_t;

static void tp_quit(void * ptr) {
	//tpool_t * tpool = (tpool_t *)ptr;
	pthread_exit(NULL);
}

static void * worker_func(void * ptr) {
	tpool_t * tpool = (tpool_t *)ptr;
	for (;;) {
		workitem_t * wi = (workitem_t *)queue_get(&(tpool->work_queue));
		func_t func = wi->func;
		void * arg = wi->arg;
		free(wi);

		if (tpool->state != TP_STOPPING || func == tp_quit) {
			func(arg);
		}
	}
	return NULL;
}

void tp_init(tpool_t * tpool, size_t nthreads) {
	queue_init(&(tpool->work_queue));
	tpool->nthreads = nthreads;
	tpool->threads = (pthread_t *)malloc(nthreads * sizeof (pthread_t));
	tpool->state = TP_RUNNING;
	for (size_t i = 0; i < nthreads; ++i) {
		pthread_create(&(tpool->threads[i]), NULL, worker_func, tpool);
	}
}

void tp_stop(tpool_t * tpool, bool finish_all_tasks) {
	if (tpool->state == TP_RUNNING) {
		tpool->state = finish_all_tasks ? TP_FINISHING : TP_STOPPING;
		for (int i = 0; i < tpool->nthreads; ++i) {
			tp_submit(tpool, tp_quit, tpool);
		}
		for (int i = 0; i < tpool->nthreads; ++i) {
			pthread_join(tpool->threads[i], NULL);
		}
	}
}

void tp_destroy(tpool_t * tpool) {
	tp_stop(tpool, false);
	free(tpool->threads);
	queue_destroy(&(tpool->work_queue));
}

bool tp_submit(tpool_t * tpool, func_t func, void * arg) {
	if (tpool->state == TP_RUNNING || func == tp_quit) {
		workitem_t * wi = (workitem_t *)malloc(sizeof (workitem_t));
		wi->func = func;
		wi->arg = arg;	
		queue_put(&(tpool->work_queue), wi);
		return true;
	}
	return false;
}
