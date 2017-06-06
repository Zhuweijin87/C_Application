#include <stdio.h>
#include <string.h>
#include "hashtable.h"

int hashCode(const char *key, int len)
{
    unsigned int  hashkey;

    return hashkey;
}

int hashtable_create(hashtable_t *hashtable, int bucket_num, int bucket_size)
{
    hashtable->bucketnum = bucket_num;
    hashtable->bucketsize = bucket_size + sizeof(hashnode_t);
    hashtable->incrementor = 10;
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