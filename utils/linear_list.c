/* 线性队列 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;

typedef struct list_s
{
	data_t	*data;
	int		size;
	int		count;
	int 	head;
	int		tail;
} list_t;

list_t *list_new(int size)
{
	list_t	*list = (list_t *)malloc(sizeof(list_t));
	list->data = (data_t *)malloc(sizeof(data_t) * size);
	list->head = list->tail = list->count = 0;
	list->size = size;
	return list;
}

int list_add(list_t *list, data_t d)
{
	list->data[list->tail] = d;
	list->tail = (list->tail+1) % list->size;
	list->count++;
	return 0;
}

int list_get(list_t *list)
{
	int 	data;
	if(list->count <= 0)
		return -1;
	data = list->data[list->head];
	list->head = (list->head+1) % list->size;
	list->count--;
	return data;
}

int list_peek(list_t *list, int idx)
{
	int  peek = (list->head + idx) % list->size;
	return list->data[peek];
}

int list_size(list_t *list)
{
	return list->count;
}

int is_empty(list_t *list)
{
	return list->head == list->tail ? 1 : 0;
}

int is_full(list_t *list)
{
	return ((list->tail + 1) % list->size) == list->head ? 1 : 0;
}

void list_clean(list_t *list)
{
	list->head = list->tail;
}

//test

void list_iter_print(list_t *list)
{
	int i;
	int size = list_size(list);
	for(i=0; i<size; i++)
		printf("%d, ", list_peek(list, i));
	printf("\n");
}

int main()
{
	list_t	*list = list_new(10);

	list_add(list, 1);
	list_add(list, 2);
	list_add(list, 3);
	list_add(list, 5);
	list_add(list, 7);

	list_iter_print(list);

	printf("list is empty: %s\n", is_empty(list) == 1 ? "YES": "NO");
	printf("list is full: %s\n", is_full(list) == 1 ? "YES" : "NO");	
	
	printf("list get : %d\n", list_get(list));
	list_iter_print(list);
	list_clean(list);
	list_iter_print(list);
	return 0;
}
