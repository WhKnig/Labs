#ifndef TREE_H
#define TREE_H

#define EXT 2
#include <stdio.h>

typedef struct node {
    unsigned info;
    struct node  *next;
} node;

typedef struct item {
    char *key;
    node *head;
} item;

typedef struct knot {
    int size;
    item **arr;
    struct knot **child;
    struct knot *parent;
} knot;

typedef struct tree {
    knot *root;
} tree;

typedef struct gnode
{
    char *key;
    unsigned info;
} gnode;

typedef char bool;

int insert_tree(tree *tr, char *key, unsigned info);
item* search_version(knot *root, char *key, int version);
int delete_version(tree *tr, char *key, int version);
void inorder_traversal(knot *root, char *low, char *high, int *found);
item* search_max_leq_key(knot *root, char *key, int *found);
void print_tree(const tree *tr);
int graf(tree *tr);
int f_in(tree *tr);
gnode* gen_nodes(int n);
void gen_tree(tree *tr, int n);


#endif
