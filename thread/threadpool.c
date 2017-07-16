/* 线程池 */
#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"

static void thread_function(void *arg);

threadpool_t *threadpool_new(int threadNum, int queueSize)
{
	threadpool_t *pool = (threadpool_t *)malloc(sizeof(threadpool_t));
	if(!pool)
	{
		return NULL;
	}

	pool->threadNum = threadNum > MAX_THREAD_COUNT ? MAX_THREAD_COUNT : threadNum;
	pool->queueSize = queueSize > MAX_QUEUE_SIZE ? MAX_QUEUE_SIZE : queueSize;

	pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * pool->threadNum);
	if(!pool->threads)
	{
		free(pool);
		return NULL;
	}

	if( pthread_mutex_init(&pool->lock, NULL) != 0 )
	{
		free(pool->threads);
		free(pool);
		return NULL;
	}

	if( pthread_cond_init(&pool->notify, NULL) != 0 )
	{
		free(pool->threads);
		free(pool);
		pthread_cond_destroy(&pool->notify);
		return NULL;
	}

	int i;
	for(i=0; i<pool->threadNum; i++)
	{
		if( pthread_create(&(pool->threads[i]), NULL, (void *)&thread_function, (void *)pool) != 0 )
		{
			free(pool->threads);
			free(pool);
			pthread_cond_destroy(&pool->notify);
			pthread_cond_destroy(&(pool->notify));
			return NULL;
		}
	}

	pool->queue = (thread_job_t *)malloc(sizeof(thread_job_t) * pool->queueSize);
	pool->workCount = 0;
	pool->close = 0;
	pool->queueHead = pool->queueTail= 0;

	return pool;
}

static void thread_function(void *arg)
{
	threadpool_t *pool = (threadpool_t *)arg;
	thread_job_t *job = NULL;

	do
	{
		pthread_mutex_lock(&pool->lock);
		while( pool->workCount == 0 && pool->close == 0 )
		{
			pthread_cond_wait(&pool->notify, &pool->lock);
		}
	
		if(pool->close)
		{
			//close threadpool
			break;
		}

		job = &(pool->queue[pool->queueHead]);
		pool->queueHead = (pool->queueHead + 1) % pool->queueSize;
		pool->workCount--;
		
		pthread_cond_broadcast(&pool->notify);

		pthread_mutex_unlock(&pool->lock);

		(job->function)(job->argv);

	} while(1);

	return ;
}

int threadpool_add(threadpool_t *pool, void (*function)(void *argv), void *argv)
{
	int		queueNext = 0;

	if(pool == NULL)
		return -1;

	pthread_mutex_lock(&pool->lock);
	queueNext = (pool->queueTail + 1) % pool->queueSize;

	do
	{
		if(pool->workCount == pool->queueSize)
		{
			pthread_cond_wait(&pool->notify, &pool->lock);
		}

		pool->queue[pool->queueTail].function = function;
		pool->queue[pool->queueTail].argv = argv;
		pool->queueTail = queueNext;
		pool->workCount++;

		pthread_cond_signal(&pool->notify);
	} while(0);

	pthread_mutex_unlock(&pool->lock);

	return 0;
}

int threadpool_destroy(threadpool_t *pool)
{
	if(pool == NULL)
		return -1;

	pthread_mutex_lock(&pool->lock);

	do
	{
		;	
	} while(1);
}

