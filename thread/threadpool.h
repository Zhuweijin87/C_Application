#ifndef _THREAD_POOL_H

#include <pthread.h>

#define  MAX_THREAD_COUNT		24
#define	 MAX_QUEUE_SIZE			512

typedef struct thread_job_s
{
	void  	(*function)(void *argv);
	void 	*argv;
} thread_job_t;

typedef struct threadpool_s
{
	pthread_t			*threads;
	pthread_mutex_t		lock;
	pthread_cond_t		notify;
	thread_job_t		*queue;

	int					threadNum;
	int					queueSize;
	int					queueHead;
	int					queueTail;
	int					workCount;
	int					close;
	
} threadpool_t;

#endif 
