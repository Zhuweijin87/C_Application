#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t	lock;
pthread_cond_t	lessMoney;
pthread_cond_t	lessGoods;

int money_deposit = 1000;
int good_stock = 0;

void *producer(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(money_deposit <= 0)
		{
			pthread_cond_wait(&lessMoney, &lock);
		}
		
		good_stock += 1;
		money_deposit -= 15;
		//usleep(50 * 1000);
		printf("producer >> good_stock:%d, money_deposit: %d\n", good_stock, money_deposit);
		if(good_stock >= 10)
		{
			pthread_cond_broadcast(&lessGoods);
		}

		pthread_mutex_unlock(&lock);
	}
}

void *consumer(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(good_stock <= 0)
		{
			pthread_cond_wait(&lessGoods, &lock);
		}
	
		good_stock -= 1;
		money_deposit += 20;
		//usleep(50 * 1000);
		printf("consumer >> good stock: %d, money deposit: %d\n", good_stock, money_deposit);

		if(money_deposit >= 200)
		{
			pthread_cond_broadcast(&lessMoney);
		}
		pthread_mutex_unlock(&lock);
	}
}

int main()
{
	pthread_t	thread[3];

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&lessMoney, NULL);
	pthread_cond_init(&lessGoods, NULL);

	pthread_create(&thread[0], NULL, producer, NULL);
	pthread_create(&thread[1], NULL, producer, NULL);
	pthread_create(&thread[2], NULL, consumer, NULL);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);

	return 0;
}
