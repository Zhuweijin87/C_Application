/* 链式链表 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef	int			data_t;
//typedef NULL		nullptr;

#define nullptr		NULL

#define t_malloc	malloc
#define t_realloc	realloc
#define t_calloc	calloc
#define	t_free		free

typedef struct node_s
{
	data_t		data;
	struct node_s *next;
}node_t;

typedef struct list_s
{
	int 	size;
	node_t	*head;
	node_t	*tail;
}list_t;

node_t *node_new(data_t data, int size)
{
	node_t	*node = t_malloc(sizeof(node_t));
	//memcpy(node->data, data, size);
	node->data = data;
	node->next = nullptr;
	return node;
}

void node_free(node_t *node)
{
	t_free(node);
}

list_t *list_new()
{
	list_t	*list = t_malloc(sizeof(list_t));
	return list;
}

void list_free(list_t **list)
{
	node_t *temp;
	while((*list)->head)
	{
		temp = (*list)->head;
		(*list)->head = (*list)->head->next;
		node_free(temp);
	}
	*list = nullptr;
}

static node_t *list_get_at(list_t *list, int position)
{
	if(list->size == 0 || position > list->size || position < 0)
		return nullptr;

	if(position == list->size)
		return list->tail;
	if(position == 0)
		return list->head;

	int  	idx;
	node_t	*temp = list->head;
	for(idx = 0; idx < position; idx++)
	{
		temp = temp->next;	
	}
	return temp;
}

int list_add_head(list_t *list, data_t data)
{
	node_t *node = node_new(data, sizeof(data));
	if(!node)	
		return -1;
	
	if(list->size == 0)
	{
		list->head = list->tail = node;
	}
	else
	{
		node->next = list->head;
		list->head = node;
	}
	list->size++;
	return 0;
}

int list_add_tail(list_t *list, data_t data)
{
	node_t	*node = node_new(data, sizeof(data));
	if(!node)
		return -1;

	if(list->size == 0)
	{
		list->tail = list->head = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
	return 0;
}

int list_add_at(list_t *list, data_t data, int pos)
{
	node_t *node = list_get_at(list, pos-1);
	if(!node)
		return -1;

	node_t *new = node_new(data, sizeof(data));
	
	new->next = node->next;
	node->next = new;
	return 0;
}

int list_reverse(list_t *list)
{
	if(list->size == 0 || list->size == 1)
		return 0;
	node_t *head = list->head;
	node_t *tail = list->tail;

	
	return 0;
}

void list_print(list_t *list)
{
	node_t *node = list->head;
	while(node)
	{
		printf("%d\t", node->data);
		node = node->next;
	}
	printf("\n");
}

int main()
{
	list_t *list = list_new();

	list_add_head(list, 12);
	list_add_head(list, 13);
	list_add_head(list, 14);
	list_add_head(list, 15);

	int i=0;
	for(i=0; i<50; i++)
		list_add_head(list, i+20);

	list_print(list);

	for(i=0; i<50; i++)
		list_add_tail(list, i+200);
	list_print(list);

	list_add_at(list, 500, 10);

	list_print(list);
	list_free(&list);
	return 0;
}
