#pragma once
#include "Pool.h"

#define MAX_RECORDS_TABLE 1024
#define TITLE_MAX 150
#define AUTHOR_MAX 50

typedef struct Record
{
    char Title[TITLE_MAX];
    char Author[AUTHOR_MAX];
    int ISBN_bottomseven;
    int Year;
} Record;

typedef struct Table
{
    int key_count;
    int keys[MAX_RECORDS_TABLE];
    Record *data[MAX_RECORDS_TABLE]; // DataPool 上のポインタ
    DataPool pool;
} Table;

void table_init(Table *t);
void table_insert(Table *, const char *, const char *, int, int, int);
char *table_search(Table *t, int key);
