#include <stdio.h>
#include <string.h>
#include "hashtable.h"

int hashCode(const char *key, int len)
{
    unsigned int  hashkey;

    return hashkey;
}

hashtable_t *hashtable_create(hashtable_t *hashtable, int bucket_num, int bucket_size)
{
	hashtable_t *hashtable = malloc(sizeof(hashtable_t));
    hashtable->number = bucket_num;
    hashtable->bucketsize = bucket_size + sizeof(hashnode_t);
    hashtable->incr = 10;
    hashtable->memory = calloc(bucket_num, hashtable->bucketsize);
    hashtable->buckets = calloc(bucket_num, sizeof(hashnode_t *));

    return 0;
}

int hashtable_destroy(hashtable_t *hashtable)
{

}

int hashtable_clean(hashtable_t *hashtable)
{
    
}

static hashnode_t *hashnode_create(char *key, char *value)
{
	hashnode_t *node = malloc(sizeof(hashnode_t));
	memcpy(node->key, key, strlen(key));
	node->value = value;
	node->next = NULL;
	return node;
}

static int hashtable_add(hashtable_t *htable, char *key, void *val, int size)
{
	;
}

int hashtable_addstring(hashtable_t *htable, char *key, char *valstring)
{
	return 0;
}

int hashtable_addnumber(hashtable_t *htable, char *key, double valdouble)
{
	return 0;
}

int hashtable_delete(hashnode_t *htable, char *key)
{
	return 0;
}




