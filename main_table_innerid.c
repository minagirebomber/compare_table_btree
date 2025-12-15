#include "headers/tableinnerid_index.h"
#include <stdio.h>

int main()
{
    Table t;
    int key1, key2, key3;
    table_init(&t);

    key1 = table_insert(&t, "Harry Potter", "J.K.Rowling", 978491, 5512377, 1997);
    key2 = table_insert(&t, "Capital", "Karl Marx", 978448, 511904, 1867);
    key3 = table_insert(&t, "Factfulness", "Hans Rosling", 978482, 2289607, 2018);

    char *v = table_search(&t, key3);
    if (v)
        printf("search 20 -> %s\n", v);

    return 0;
}