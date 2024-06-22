#ifndef MAIN_H
#define MAIN_H

#include "global.h"

#include <pthread.h>

typedef struct _foo_ts {
	pthread_mutex_t mutex;
	int val;
} foo_ts;

extern foo_ts foo;

extern void *main_thread0(void *para);
extern void *main_thread1(void *para);
extern void *main_thread2(void *para);
extern void *main_thread3(void *para);

#endif // MAIN_H