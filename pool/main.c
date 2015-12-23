/*test tpool*/

#include "tpool.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *func(void *argv);


int 
main(void) {
	thread_pool_t *tpool;	
	thread_t *tp;
	task_t *task;

	tpool = thread_pool_init(5);

	if (tpool == NULL) {
		printf("init thread pool fail");
		return -1;
	}

	tp = thread_pool_get(tpool);

	if (tp == NULL) {
		printf("fail to get thread.");
		free(tpool);
		return -1;
	}

	pthread_mutex_lock(&tp->thd.lock);

	task = (task_t *)malloc(sizeof(task_t));	

	if (task == NULL) {
		printf("init task fail.");
	}	

	task->next = NULL;
	task->ctx  = NULL;
	task->handler = func;
	
	tp->thd.taskqueue = task;

	tp->thd.busy = 1;	
	pthread_mutex_unlock(&tp->thd.lock);

	pthread_cond_signal(&tp->thd.cond);

	
	printf("in main :pid[%lu],tid[%lu],process ....\n",(unsigned long)getpid(),(unsigned long)pthread_self());

	sleep(5);
	thread_pool_destroy(tpool);

	return 0;
}

void *func(void *argv) {
	printf("pid[%lu],tid[%lu],process ....\n",(unsigned long)getpid(),(unsigned long)pthread_self());
	return NULL;
}
