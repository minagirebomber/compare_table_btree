
#pragma once

#define DATA_SIZE 256
#define MAX_RECORDS_POOL 1024

typedef struct DataPool
{
    char pool[MAX_RECORDS_POOL][DATA_SIZE];
    int next_free;
} DataPool;

void pool_init(DataPool *p);
void *pool_alloc(DataPool *p);