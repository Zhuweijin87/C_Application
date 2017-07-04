/* 简单的线程池 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct thread_status_s
{
	pthread_t	thread;
	int			status;
} thread_t;

typedef struct thread_s
{
	int			num;
	thread_t	*threads;
} Thread;

/* 初始化线程 */
void ThreadInit(Thread *thread, int num)
{
	thread->num = num;
	thread->threads = calloc(num, sizeof(thread_t));
}

int ThreadRun(Thread *thread, void *(func)(void *arg), void *arg)
{
	int		ret;
	int		i;

	for(i = 0; i<thread->num; i++)
	{
		if(thread->threads[i].status == 0)
		{
			ret = pthread_create(&thread->threads[i].thread, NULL, func, arg);
			if(ret == -1)
			{
				return -1;
			}
		}
	}
	return 0;
}

void *_thread_exit()
{
	;
}

void ThreadWait(Thread *thread)
{
	int		i;
	for(i=0; i<thread->num; i++)
	{
		pthread_join(thread->threads[i].thread, NULL);
	}
}

void ThreadWaitTimeout(Thread *thread, int timeout)
{
	;
}

void *test1(void *arg)
{
	int i;
	for(i=0; i<10; i++)
	{
		printf("test1 ...\n");
		usleep(200 * 1000);
	}

	char ret[] = "test1 is reurned";
	return (void **)&ret;
}

void *test2(void *arg)
{
	int i;
	for(i=0; i<10; i++)
	{
		printf("test2 ...\n");
		usleep(300 * 1000);
	}

	char ret[] = "test2 is reurned";
	return (void **)&ret;
}

int main()
{
	Thread thread;

	ThreadInit(&thread, 4);

	ThreadRun(&thread, &test1, NULL);
	ThreadRun(&thread, &test2, NULL);

	//ThreadWait(&thread);
	pthread_join(thread.threads[0].thread, NULL);
	pthread_join(thread.threads[1].thread, NULL);

	return 0;
}
