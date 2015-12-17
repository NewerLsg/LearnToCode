#ifndef TPOOL_H
#define TPOOL_H

#include<stddef.h>
#include<pthread.h>

#define MAXNODE 128

#define offset(st,mem) \
		((int )&(((st *)0)->mem))

#define free_list(st, head)   		\
		do{							\
			st tmp; 				\
			while(head){ 			\
				tmp = head;			\
				head = head->next;	\
				free(tmp);			\
			}						\
		}while(0)

typedef struct task_s {
	unsigned int 		type;
	void 				*ctx;
	void 		 		*(*handler)(void *data);
	struct task_s 		*next;
}task_t;

typedef struct thread_ctx_s {
	pthread_t 			tid;	
	pthread_mutex_t 	lock;
	pthread_cond_t		cond;
	unsigned char 		busy;
	void 				*ctx;	
    void           		(*handler)(void *data);	
	task_t 				*taskqueue;
}thread_ctx_t;

typedef struct thread_s{
	struct thread_s 	*prev;
	struct thread_s 	*next;
	thread_ctx_t 		 thd;
}thread_t;

typedef struct thread_pool_s {
	size_t 				max;	 	/*nodes count*/ 
	size_t 				used;
	pthread_mutex_t 	lock;
	thread_t 			*array;
}thread_pool_t;

/*init pool  */
thread_pool_t *thread_pool_init(size_t size);

/*get resource from pool*/
thread_t *thread_pool_get(thread_pool_t *pool);

int thread_pool_free(thread_t *node);

/*reset the pool*/
void *thread_pool_reset(thread_pool_t *pool);

/*destroy pool*/
int thread_pool_destroy(thread_pool_t *pool);

#endif
