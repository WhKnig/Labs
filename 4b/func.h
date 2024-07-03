#include "tree.h"
#ifndef F_H
#define F_H


void delete_tree(knot *root);
tree* create_tree();
knot* create_knot();
item* create_item(char *key, unsigned info);
node* create_node(unsigned info);
void split_child(knot *parent, int index, knot *child);
void insert_non_full(knot *root, char *key, unsigned info);
void print_item_search(item *element, int version);
void print_knot_screen(const char* prefix, const knot* node, int isLeft);
bool tree_is_empty(tree *tr);
int get_releases(item *list);
int remove_tree(tree *tr, char *key);
void process_tree(tree *wood);
bool knot_is_sheet(knot *ptr);
int choose_index(knot *ptr, char *key);
knot *process1(knot *ptr, int index);
knot *process2(knot *ptr, int index);
bool knot_contains(knot *ptr, char *key);
void remove_item(knot *ptr, int index);
void freenodes(gnode *nodes);


#endif