#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t		lock;
pthread_cond_t		run;

int init()
{
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&run, NULL);
}

void *producer(void *arg)
{
	int i;
	for(i=0; i<10; i++)
		printf("I am producer\n");
}

void *consumer(void *arg)
{
	int i;
	for(i=0; i<10; i++)
		printf("I am consumer\n");
}

void *notice(void *arg)
{
	while(1)
	{
		sleep(3);
		pthread_cond_signal(&run);
		//break;
	}
}

void *handle(void *arg)
{

	while(1)
	{
		pthread_mutex_lock(&lock);

		pthread_cond_wait(&run, &lock);
		printf("Thread is Run..\n");
		usleep(500 * 1000);
		pthread_mutex_unlock(&lock);
	}
}

int main()
{
	int 		ret;
	void 		*res;
	pthread_t	threads[2];

	init();

	pthread_create(&threads[0], NULL, notice, NULL);
	pthread_create(&threads[1], NULL, handle, NULL);	

	
	ret = pthread_join(threads[0], NULL);
	if(ret)
		printf("pthread_join fail\n");
	else
		printf("pthread_join ok\n");

	ret = pthread_join(threads[1], NULL);
	if(ret)
		 printf("pthread_join fail\n");
    else
        printf("pthread_join ok\n");

	return 0;
}
