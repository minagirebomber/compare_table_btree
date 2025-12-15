#include "headers/btree_index.h"
#include <stdio.h>

int main()
{
    BTree tree;
    btree_init(&tree);

    btree_insert(&tree, "Harry Potter", "J.K.Rowling", 978491, 5512377, 1997);
    btree_insert(&tree, "Capital", "Karl Marx", 978448, 511904, 1867);
    btree_insert(&tree, "Factfulness", "Hans Rosling", 978482, 2289607, 2018);

    char *v = btree_search(&tree, 978482);
    if (v)
        printf("search 20 -> %s\n", v);

    return 0;
}