#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

char *gen_key() {
    char *key = (char *)malloc(6 * sizeof(char));
    for (int i = 0; i < 5; i++) {
        key[i] = 'a' + rand() % 26;
    }
    key[5] = '\0';
    return key;
}

unsigned gen_info() {
    return rand() % 1000;
}

void gen_tree(tree *tr, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        char *key = gen_key();
        unsigned info = gen_info();
        insert(tr, key, info);
        free(key);
    }
}

gnode* gen_nodes(int n)
{
    gnode *nodes = (gnode*)calloc(n, sizeof(gnode));

    for(int i = 0; i < n; i++)
    {
        nodes[i].key = gen_key();
        nodes[i].info = gen_info();
    }

    return nodes;
}