#include "headers/btree_index.h"

static BTreeNode *btree_create_node(int is_leaf)
{
    BTreeNode *node = malloc(sizeof(BTreeNode));
    node->key_count = 0;
    node->is_leaf = is_leaf;
    for (int i = 0; i < BTREE_ORDER; i++)
        node->children[i] = NULL;
    return node;
}

static Record *create_record(
    BTree *t,
    const char *title,
    const char *author,
    int isbn_bottomseven,
    int year)
{
    Record *r;
    r = pool_alloc(&t->pool);
    strncpy(r->Title, title, TITLE_MAX);
    strncpy(r->Author, author, AUTHOR_MAX);
    r->ISBN_bottomseven = isbn_bottomseven;
    r->Year = year;
    return r;
}

void btree_init(BTree *t)
{
    pool_init(&t->pool);
    t->root = btree_create_node(1);
}

static Record *btree_search_node(BTreeNode *node, int key)
{
    int i = 0;
    while (i < node->key_count && key > node->keys[i])
        i++;

    if (i < node->key_count && key == node->keys[i])
        return node->records[i];

    if (node->is_leaf)
        return NULL;

    return btree_search_node(node->children[i], key);
}

Record *btree_search(BTree *t, int key)
{
    if (!t->root)
        return NULL;
    return btree_search_node(t->root, key);
}

static void btree_split_child(BTreeNode *parent, int index)
{
    BTreeNode *full = parent->children[index];
    BTreeNode *new_node = btree_create_node(full->is_leaf);

    int mid = BTREE_MAX_KEYS / 2; // =1

    /* new_node に後半を移す */
    new_node->key_count = BTREE_MAX_KEYS - mid - 1;

    for (int i = 0; i < new_node->key_count; i++)
    {
        new_node->keys[i] = full->keys[mid + 1 + i];
        new_node->records[i] = full->records[mid + 1 + i];
    }

    if (!full->is_leaf)
    {
        for (int i = 0; i < new_node->key_count + 1; i++)
            new_node->children[i] = full->children[mid + 1 + i];
    }

    full->key_count = mid;

    /* parent の子をずらす */
    for (int i = parent->key_count; i >= index + 1; i--)
        parent->children[i + 1] = parent->children[i];

    parent->children[index + 1] = new_node;

    /* parent のキーをずらす */
    for (int i = parent->key_count - 1; i >= index; i--)
    {
        parent->keys[i + 1] = parent->keys[i];
        parent->records[i + 1] = parent->records[i];
    }

    /* 中央キーを親へ昇格 */
    parent->keys[index] = full->keys[mid];
    parent->records[index] = full->records[mid];
    parent->key_count++;
}

static void btree_insert_nonfull(BTreeNode *node, Record *rec, int key)
{
    int i = node->key_count - 1;

    if (node->is_leaf)
    {
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            node->records[i + 1] = node->records[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->records[i + 1] = rec;
        node->key_count++;
    }
    else
    {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;

        if (node->children[i]->key_count == BTREE_MAX_KEYS)
        {
            btree_split_child(node, i);
            if (key > node->keys[i])
                i++;
        }
        btree_insert_nonfull(node->children[i], rec, key);
    }
}

void btree_insert(
    BTree *t,
    const char *title,
    const char *author,
    int isbn_topsix,
    int isbn_bottomseven,
    int year)
{
    Record *rec = create_record(t, title, author, isbn_bottomseven, year);
    BTreeNode *r = t->root;
    if (r->key_count == BTREE_MAX_KEYS)
    {
        BTreeNode *new_root = btree_create_node(0);
        new_root->children[0] = r;
        t->root = new_root;
        btree_split_child(new_root, 0);
        btree_insert_nonfull(new_root, rec, isbn_topsix);
    }
    else
    {
        btree_insert_nonfull(r, rec, isbn_topsix);
    }
}