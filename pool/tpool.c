#include "tpool.h"

#include <stdlib.h>
#include <stdio.h>

void *thread_cycle(void *argv);
void thread_destroy(thread_t *thread);

thread_pool_t *thread_pool_init(size_t size) {
	thread_pool_t *pool;
	pthread_mutex_t *lock;

	if (size < 0) {
		size = MAXNODE;
	}

	pool = (thread_pool_t *)malloc(sizeof(thread_pool_t));
	
	if (pool == NULL) {
		return NULL;
	}

	if (pthread_mutex_init(&pool->lock, NULL) != 0){
		free(pool);
		return NULL;
	}

	pool->max 	= size;
	pool->used 	= 0;
	pool->array = NULL;
		
	return pool;
}


/*get resource from pool*/
thread_t *thread_pool_get(thread_pool_t *pool) {
	thread_t *thread;	
	int err;

	if (pool == NULL) return NULL;	
	
	pthread_mutex_lock(&pool->lock);
	
	if (pool->used >= pool->max) {
		pthread_mutex_unlock(&pool->lock);	

		return NULL;
	}

	thread = pool->array;
	while (thread != NULL && thread->thd.busy != 1) {
		thread = thread->next;	
	}

	do {
		if (thread == NULL) {
			thread = (thread_t *)malloc(sizeof(thread_t));
			
			if (thread == NULL) {
				break;
			}

			if (pthread_mutex_init(&thread->thd.lock, NULL) !=0) {
				free(thread);
				break;
			}

			if (pthread_cond_init(&thread->thd.cond, NULL) != 0) {
				pthread_mutex_destroy(&thread->thd.lock);	
				free(thread);
				break;
			}

			thread->thd.busy 		= 1;
			thread->thd.ctx  		= NULL;
			thread->thd.handler 	= NULL;
			thread->thd.taskqueue 	= NULL;
	
			thread->prev 			= NULL;
			thread->next 			= pool->array;	

			if (pool->array != NULL) {
				pool->array->prev 		= thread;
			}

			pool->array 			= thread;
			
			pthread_create(&thread->thd.tid, NULL, thread_cycle, thread);
		}
		
		pool->used++;
		
	}while(0);

	pthread_mutex_unlock(&pool->lock);	

	return thread;
}


/*	 free node 	*/
int thread_pool_free(thread_t *thread){

	if (thread != NULL) return 0;	
	
	pthread_mutex_lock(&thread->thd.lock);				
	
	thread->thd.busy = 0;

	thread->thd.taskqueue = NULL;

	pthread_mutex_unlock(&thread->thd.lock);				

	return 0;
}


/*reset the pool*/
void *thread_pool_reset(thread_pool_t *pool){
	return pool;
}


/*destroy pool*/
int thread_pool_destroy(thread_pool_t *pool) {
	thread_t *thread, *tmp;	
	
	if (pool != NULL) return 0;
	
	thread =  pool->array;

	while (thread) {
		tmp = thread;	
		thread = thread->next;
		thread_destroy(tmp);
	}		
	
	pthread_mutex_destroy(&pool->lock);
	free(pool);

	return 0;		
}

void *thread_cycle(void *argv) {
	thread_t *thread;	
	task_t   *task, *tmp;

	thread = (thread_t *)argv;

	while(1) {
		pthread_mutex_lock(&thread->thd.lock);


		while(thread->thd.busy == 0 || thread->thd.taskqueue == NULL) {
			pthread_cond_wait(&thread->thd.cond, &thread->thd.lock);
		}	
		
		task = thread->thd.taskqueue;
		thread->thd.busy = 0;	

		pthread_mutex_unlock(&thread->thd.lock);
		
		while(task){
			tmp = task;
			task = task->next;
			tmp->handler(tmp->ctx);		
			free(tmp->ctx);
			free(tmp);
		}
	}
	return 0;
}

void thread_destroy(thread_t *thread){
	task_t *task, *tmp;	
	
	if (thread == NULL) return ;
	
	pthread_mutex_destroy(&thread->thd.lock);	

	pthread_cond_destroy(&thread->thd.cond);	

	free(thread->thd.ctx);

	free(thread);
	
	return ;
}
