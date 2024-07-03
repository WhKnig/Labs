#include "tree.h"
#ifndef DILOGS_H
#define DILOGS_H


int dilog_detour(tree *tr);
int dilog_insert(tree *tr, char *key);
int dilog_delete(tree *tr, char *key);
int dilog_search(tree *tr, char *key);
int dilog_sp_search(tree *tr, char *key);
int dilog_test(tree *tr);
int testing(tree *tr, gnode *nodes, int n);


#endif