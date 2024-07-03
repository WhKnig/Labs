#ifndef TREE_H
#define TREE_H

typedef struct node
{
    char *key;
    unsigned info;
    struct node *right;
    struct node *left;
} node;


typedef struct gnode
{
    char *key;
    unsigned info;
} gnode;


typedef struct tree
{
    node *head;
} tree;

int insert(tree *tr, char *key, unsigned info);
void printBinaryTree(const tree *tr);
int delete_k(tree *tr, const char *key);
int f_in(tree *tr);
void freeTree(tree *tr);
void obhod(const tree *tr, const char *key);
int graf(tree *tr);
node* sp_search(const tree *tr, const char *key, int ver);
void gen_tree(tree *tr, int n);
void freenodes(gnode *nodes);
gnode* gen_nodes(int n);
int testing(tree *tr, gnode *nodes, int n);
node* poisk(const tree *tr, const char *key, int ver);
void obhod_test(const tree *tr, const char *key);

#endif