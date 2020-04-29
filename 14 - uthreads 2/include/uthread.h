#ifndef UTHREAD_H
#define UTHREAD_H

// System management
void ut_init();
void ut_run();
void ut_end();

// UThread API
void ut_create(void (*start_routine) (void *), void *arg);
void ut_yield();
void ut_exit();

#endif // UTHREAD_H
