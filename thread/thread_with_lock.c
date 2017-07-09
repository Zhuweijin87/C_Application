#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t		lock;

int  n = 0;
void *add(void *arg)
{
	int	i;
	int v = *(int *)arg;

	for(i=0; i<20; i++)
	{
		pthread_mutex_lock(&lock);
		printf("%d\n", n++);
		pthread_mutex_unlock(&lock);
	}

	return (void *)0;
}

int main()
{
	int 		ret;
	int 		v = 0;
	pthread_t	threads[2];

	pthread_mutex_init(&lock, NULL);

	pthread_create(&threads[0], NULL, add, &v);
	pthread_create(&threads[1], NULL, add, &v);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	printf("Last N is :%d\n", n);
	return 0;
}
