/* 哈希表 */

#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#define HASH_KEY_LEN    		64
#define HASH_BULK_DEFAULT_SIZE	256

typedef struct hashnode_s
{
    char  key[HASH_KEY_LEN + 1];
    void  *value;
} hashnode_t;

typedef struct hashtable_s
{
    int         	bulksize;
    int         	valuesize;
    int         	increment;
    char       		*memory;
    hashnode_t 		**bulks;
} hashtable_t;

#define t_malloc		malloc
#define t_realloc		malloc
#define t_calloc		calloc
#define t_free			free

#endif
