#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t		lock;
pthread_cond_t		lessMoney;
pthread_cond_t		lessGoods;

/* 生产 */
void *producer(void)
{

}

/* 消费 */
void *consumer(void)
{

}


int main()
{
	int 		ret;
	pthread_t	threads[4];

	ret = pthread_mutex_init(&lock, NULL);
	if(ret)
	{
		printf("");
		exit(1);
	}
	
	ret = pthread_cond_init(&lessMoney, NULL);
	if(ret)
	{
		printf("");
		exit(1);
	}

	pthread_create(&thread[0], NULL, producer, NULL);
	pthread_Create(&thread[1], NULL, consumer, NULL);	
	
	return 0;
}
