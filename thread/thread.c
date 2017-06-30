#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

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

void *_thread_exit()
{
	printf("exit\n");
}

int main()
{
	int 		ret;
	void 		*res;
	pthread_t	threads[2];

	pthread_create(&threads[0], NULL, producer, NULL);
	pthread_create(&threads[1], NULL, consumer, NULL);	

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
	//sleep(2);

	return 0;
}
