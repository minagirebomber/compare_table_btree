#include "headers/table_index.h"
#include "headers/Pool.h"
#include <stdio.h>
#include <string.h>

void table_init(Table *t)
{
    t->key_count = 0;
    pool_init(&t->pool);
}

void table_insert(
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
    t->keys[i] = isbn_topsix;
    strncpy(record->Title, title, TITLE_MAX);
    strncpy(record->Author, author, AUTHOR_MAX);
    record->ISBN_bottomseven = isbn_bottomseven;
    record->Year = year;
    t->data[i] = record;
    t->key_count++;
}

char *table_search(Table *t, int key)
{
    for (int i = 0; i < t->key_count; i++)
        if (t->keys[i] == key)
            return t->data[i]->Title;
    return NULL;
}
