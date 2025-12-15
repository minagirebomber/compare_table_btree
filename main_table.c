#include "headers/table_index.h"
#include <stdio.h>

int main()
{
    Table t;
    table_init(&t);

    table_insert(&t, "Harry Potter", "J.K.Rowling", 978491, 5512377, 1997);
    table_insert(&t, "Capital", "Karl Marx", 978448, 511904, 1867);
    table_insert(&t, "Factfulness", "Hans Rosling", 978482, 2289607, 2018);

    char *v = table_search(&t, 978482);
    if (v)
        printf("search 20 -> %s\n", v);

    return 0;
}