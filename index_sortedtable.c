#include "headers/table_index.h"
#include "headers/Pool.h"
#include <stdio.h>
#include <string.h>
#include <memory.h>
// found : flag=1, return index
// not found : *flag=0, return index to insert
int binary_search(Table *t, int key, int *flag)
{
    int left = 0;
    int right = t->key_count;

    while (left < right)
    {
        size_t mid = (left + right) / 2;

        if (t->keys[mid] == key)
        {
            *flag = 1;
            return (int)mid;
        }
        else if (t->keys[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    *flag = 0;
    return left;
}

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

    int i, flag;
    i = binary_search(t, isbn_topsix, &flag);
    if (flag == 1)
        return;

    memcpy(&(t->keys[i + 1]), &(t->keys[i]), (t->key_count - i) * sizeof(int));
    memcpy(&(t->data[i + 1]), &(t->data[i]), (t->key_count - i) * sizeof(Record *));
    t->keys[i] = isbn_topsix;

    Record *record = pool_alloc(&t->pool);
    if (!record)
        return;

    strncpy(record->Title, title, TITLE_MAX);
    strncpy(record->Author, author, AUTHOR_MAX);
    record->ISBN_bottomseven = isbn_bottomseven;
    record->Year = year;
    t->data[i] = record;
    t->key_count++;
}

char *table_search(Table *t, int key)
{
    int flag;
    int i = binary_search(t, key, &flag);

    if (flag)
        return t->data[i]->Title;
    else
        return NULL;
}
