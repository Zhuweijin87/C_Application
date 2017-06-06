#ifndef _DATA_POOL_H
#define _DATA_POOL_H

typedef struct data_node_s
{
    int   type;
    int   flag;
    void  *value;
} datanode_t;

typedef struct data_pool_t
{
    int         quantity;
    int         eltsize;
    char        *memory;
    datanode_t  **buckets;
} datapool_t;

#define TYPE_LONG   0x01
#define TYPE_DOUBLE 0x02
#define TYPE_STRING 0x03
#define TYPE_STRUCT 0x04

#endif
