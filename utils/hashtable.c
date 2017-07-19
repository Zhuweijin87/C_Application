#include <stdio.h>
#include <string.h>
#include "hashtable.h"

int hashCode(const char *key, int len)
{
    unsigned int  hash;

    return hash;
}

hashtable_t *hashtable_create(int bulksize, int eltsize)
{
	hashtable_t *hashtbl = t_malloc(sizeof(hashtable_t));
	if(!hashtable)
		return ptr_null;
	
	hashtbl->bulks = t_calloc(bulksize, sizeof(hashnode_t *));
    return hashtbl;
}

int hashtable_destroy(hashtable_t *hashtable)
{
	
}

int hashtable_clean(hashtable_t *hashtable)
{
    
}

static hashnode_t *hashnode_create(char *key, void *value)
{
	hashnode_t	*bulk = t_malloc(sizeof(hashnode_t));
	strncpy(bulk->key, key, 64);
	bulk->value = t_memdup(value);
	return node;
}

static int hashtbl_add(hashtable_t *htable, char *key, void *val, int size)
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


