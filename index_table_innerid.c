#include "headers/tableinnerid_index.h"
#include "headers/Pool.h"
#include <stdio.h>
#include <string.h>

void table_init(Table *t)
{
    t->key_count = 0;
    pool_init(&t->pool);
}

int table_insert(
    Table *t,
    const char *title,
    const char *author,
    int isbn_topsix,
    int isbn_bottomseven,
    int year)
{
    if (t->key_count >= 1024)
        return;
    int i = t->key_count;
    Record *record = pool_alloc(&t->pool);
    if (!record)
        return;
    t->keys[i] = i; // verbose
    strncpy(record->Title, title, TITLE_MAX);
    strncpy(record->Author, author, AUTHOR_MAX);
    record->ISBN_topsix;
    record->ISBN_bottomseven = isbn_bottomseven;
    record->Year = year;
    t->data[i] = record;
    t->key_count++;
    return t->key_count;
}

char *table_search(Table *t, int key)
{
    return t->data[key]->Title;
}
