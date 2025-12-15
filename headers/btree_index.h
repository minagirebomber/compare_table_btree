#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pool.h"

#define BTREE_ORDER 4
#define BTREE_MAX_KEYS (BTREE_ORDER - 1)

#define TITLE_MAX 150
#define AUTHOR_MAX 50

/* =======================
   Record
   ======================= */

typedef struct Record
{
    char Title[TITLE_MAX];
    char Author[AUTHOR_MAX];
    int ISBN_bottomseven;
    int Year;
} Record;

/* =======================
   BTree Node
   ======================= */

typedef struct BTreeNode
{
    int key_count;
    int keys[BTREE_MAX_KEYS];
    Record *records[BTREE_MAX_KEYS];
    struct BTreeNode *children[BTREE_ORDER];
    int is_leaf;
} BTreeNode;

/* =======================
   BTree
   ======================= */

typedef struct BTree
{
    BTreeNode *root;
    DataPool pool;
} BTree;

void btree_init(BTree *);
Record *btree_search(BTree *, int);
void btree_insert(BTree *, const char *, const char *, int, int, int);

