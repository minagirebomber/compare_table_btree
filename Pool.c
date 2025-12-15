#include "headers/Pool.h"
#include <string.h>

void pool_init(DataPool *p)
{
    p->next_free = 0;
}

void *pool_alloc(DataPool *p)
{
    if (p->next_free >= MAX_RECORDS_POOL)
        return NULL;
    char *dst = p->pool[p->next_free++];
    memset(dst, 0, DATA_SIZE);
    return dst;
}