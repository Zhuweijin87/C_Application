/* 哈希表 */

#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#define HASH_KEY_LEN    64

typedef struct hashnode_s
{
    char  key[HASH_KEY_LEN + 1];
    void  *value;
} hashnode_t;

typedef struct hashtable_s
{
    int         bucketnum;
    int         bucketsize;
    int         incrementor;
    char       *memory;
    hashnode_t **buckets;
} hashtable_t;

#endif
