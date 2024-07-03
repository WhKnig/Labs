#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "func.h"


int insert_tree(tree *tr, char *key, unsigned info) {
    knot *r = tr->root;
    if (r->size == 2 * EXT - 1) {
        knot *s = create_knot();
        tr->root = s;
        s->child[0] = r;
        split_child(s, 0, r);
        insert_non_full(s, key, info);
    } else {
        insert_non_full(r, key, info);
    }
    return 0;
}


item* search_version(knot *root, char *key, int version) {
    if (root == NULL) {
        return NULL;
    }

    int i = 0;
    while (i < root->size && strcmp(key, root->arr[i]->key) > 0) {
        i++;
    }

    if (i < root->size && strcmp(key, root->arr[i]->key) == 0) {
        node *current = root->arr[i]->head;
        int count = 1;

        while (current != NULL && count < version) {
            current = current->next;
            count++;
        }

        if (current != NULL && count == version) {
            return root->arr[i];
        } else {
            return NULL;
        }
    }

    if (root->child[0] == NULL) {
        return NULL;
    } else {
        return search_version(root->child[i], key, version);
    }
}


int delete_version(tree *tr, char *key, int version) {
   
    item *list = search_version(tr->root, key, version);
    if(list == NULL){return 1;}
	const int cnt = get_releases(list);
    if (cnt == 1) {

        remove_tree(tr, key);
        return 0;
    }


    node *prev = NULL;
    node *curr = list->head;
    int count = 1;
    while (curr != NULL && count < version) {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if (curr != NULL && count == version) {
        if (prev == NULL) {
            
            list->head = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
        return 0;
    } else {
        return 1;
    }
}



void inorder_traversal(knot *root, char *low, char *high, int *found) {
    if (root == NULL) {
        return;
    }

    int i;
    for (i = 0; i < root->size; i++) {
        if (root->child[0] != NULL) {
            inorder_traversal(root->child[i], low, high, found);
        }

        if (strcmp(root->arr[i]->key, low) >= 0 && strcmp(root->arr[i]->key, high) <= 0) {
            (*found)++;
            printf("Key: %s\n", root->arr[i]->key);
        }
    }

    if (root->child[0] != NULL) {
        inorder_traversal(root->child[i], low, high, found);
    }
}


item* search_max_leq_key(knot *root, char *key, int *found) {
    if (root == NULL) {
        return NULL;
    }

    item *result = NULL;
    int i = 0;

    while (i < root->size && strcmp(root->arr[i]->key, key) <= 0) {
        if (strcmp(root->arr[i]->key, key) <= 0) {
            (*found)++;
            return root->arr[i];
        }
        result = root->arr[i];
        i++;
    }

    if (root->child[0] != NULL) {
        item *candidate = search_max_leq_key(root->child[i], key, found);
        if (candidate != NULL) {
            result = candidate;
        }
    }

    return result;
}


void print_tree(const tree *tr) {
    if (tr->root != NULL) {
        print_knot_screen("", tr->root, 0);
    }
}
