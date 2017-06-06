#include <stdio.h>
#include <string.h>
#include "datapool.h"

#define _total_memory_size(datapool) (datapool->quantity * (datapool->eltsize + sizeof(datanode_t)))
#define _total_buckets_size(datapool) (datapool->quantity * sizeof(datanode_t *))
#define _every_bucket_size(datapool) (datapool->eltsize + sizeof(datanode_t))

/* 创建datapool */
int datapool_create(datapool_t *datapool, int quantity, int eltsize)
{
    datapool->quantity = quantity;
    datapool->eltsize = eltsize;
    //datapool->eltsize = eltsize + sizeof(datanode_t);
    datapool->memory = calloc(quantity, eltsize + sizeof(datanode_t));
    datapool->buckets = calloc(quantity, sizeof(datanode_t *));
    return 0;
}

/* 销毁datapool */
void datapool_destroy(datapool_t *datapool)
{
    free(datapool->memory);
    free(datapool->buckets);
    datapool->memory = NULL;
    datapool->buckets = NULL;
    return ;
}

void datapool_clean(datapool_t *datapool)
{
    memset(datapool->memory, 0, _total_mem_size(datapool));
    memset(datapool->buckets, 0, sizeof(datanode_t *));
}

static int __set_datapool_value(datapool_t *datapool, int dataId, int type, size_t dataSize, void *data)
{
    if ( dataId < 0 || dataId > datapool->quantity )
        return -1;
    
    datanode_t *node = datapool->buckets[dataId];   
    if (node == NULL)
    {
        node = (datanode_t *)(datapool->memory + dataId * _every_bucket_size(datapool));       
    }
    node->value = (char *)node + sizeof(datanode_t);
    memcpy(node->value, data, dataSize);
    node->flag = 1;
    node->type = type;
    return 0;
}

static int __get_datapool_value(datapool_t *datapool, int dataId, int type, size_t datasize, void *data)
{
    if (dataId < 0 || dataId > datapool->quantity)
        return -1;
    
    datanode_t *node = datapool->buckets[dataId];
    if(node == NULL)
        return -2;
    
    memcpy(data, node->value, datasize);

    return 0;
}

/* Setter 与 Getter 方法 */

int datapool_set_long(datapool_t *datapool, int dataId, long value)
{
    return __set_datapool_value(datapool, dataId, TYPE_LONG, sizeof(long), &value);
}

int datapool_set_double(datapool_t *datapool, int dataId, double value)
{
    return __set_datapool_value(datapool, dataId, TYPE_DOUBLE, sizeof(double), &value);
}

int datapool_set_string(datapool_t *datapool, int dataId, char *value, int size)
{
    return __set_datapool_value(datapool, dataId, TYPE_STRING, size, value);
}

int datapool_get_long(datapool_t *datapool, int dataId, long *value)
{
    return __get_datapool_value(datapool, dataId, TYPE_LONG, sizeof(long), value);
}

int datapool_get_double(datapool_t *datapool, int dataId, double *value)
{
    return __get_datapool_value(datapool, dataId, TYPE_DOUBLE, sizeof(double), value);
}

int datapool_get_string(datapool_t *datapool, int dataId, char *value, int size)
{
    return __get_datapool_value(datapool, dataId, TYPE_STRING, size, value);
}