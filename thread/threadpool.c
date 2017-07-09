/* 线程池 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct job_list_s
{
	void  *argv;
	void *(*func)(void *argv);
	struct job_list_s *next;
} JobList;

typedef struct threadpool_s
{
	int				numOfthread;
	pthread_t		*threads;
	pthread_mutex_t	lock;
	pthread_cond_t	isIdle;
	pthread_cond_t	isBusy;
	JobList			*head;
	JobList			*tail;	
} ThreadPool;

ThreadPool *ThreadPoolNew(int num)
{
	ThreadPool *threadpool = (ThreadPool *)malloc(sizeof(ThreadPool));
	threadpool->numOfthread = num;
	threadpool->threads = calloc(num, sizeof(pthread_t));
	threadpool->head = NULL;
	threadpool->tail = NULL;

	for(i=0; i<num; i++) 
	{
		ret = pthread_create(&threadpool->threads[i], NULL, HandleFunction, NULL);
		if(ret == -1)
		{
			goto error;
		}
	}

	ret = pthread_mutex_init(&threadpool->lock, NULL);
	if(ret == -1)
	{
		goto error;
	}

	return threadpool;

error:
	free(threadpool->threads);
	free(threadpool);

	return NULL;	
}

void *HandleFunction(void *args)
