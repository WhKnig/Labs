#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "func.h"

void freenodes(gnode *nodes)
{
    for(int i = 0; i < 100; i++)
    {
        if(nodes[i].key != NULL)
        {
            free(nodes[i].key);
        }
    }
    free(nodes);
}

bool tree_is_empty(tree *tr)
{
	if (tr->root == NULL || tr->root->size == 0)
	{
		return 1;
	}
	return 0;
}

void delete_tree(knot *root) {
    if (root != NULL) {
        for (int i = 0; i <= root->size; i++) {
            delete_tree(root->child[i]);
        }

        for (int i = 0; i < root->size; i++) {
            free(root->arr[i]->key);
            node *current = root->arr[i]->head;
            while (current != NULL) {
                node *temp = current;
                current = current->next;
                free(temp);
            }
            free(root->arr[i]);
        }
        free(root->arr);
        free(root->child);
        free(root);
    }
}

tree* create_tree() {
    tree *tr = (tree*)malloc(sizeof(tree));
    tr->root = create_knot();
    return tr;
}

knot* create_knot() {
    knot *new_knot = (knot*)malloc(sizeof(knot));
    if (new_knot == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_knot->size = 0;
    new_knot->arr = (item**)malloc((2 * EXT - 1) * sizeof(item*));
    new_knot->child = (knot**)malloc(2 * EXT * sizeof(knot*));
    
    if (new_knot->arr == NULL || new_knot->child == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_knot);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < (2 * EXT - 1); i++) {
        new_knot->arr[i] = NULL;
    }
    for (int i = 0; i < 2 * EXT; i++) {
        new_knot->child[i] = NULL;
    }

    new_knot->parent = NULL;
    return new_knot;
}


node* create_node(unsigned info) {
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->info = info;
    new_node->next = NULL;
    return new_node;
}


void split_child(knot *parent, int index, knot *child) {
    knot *new_knot = create_knot();
    new_knot->size = EXT - 1;

    for (int j = 0; j < EXT - 1; j++) {
        new_knot->arr[j] = child->arr[j + EXT];
    }

    if (child->child[0] != NULL) {
        for (int j = 0; j < EXT; j++) {
            new_knot->child[j] = child->child[j + EXT];
        }
    }

    child->size = EXT - 1;

    for (int j = parent->size; j >= index + 1; j--) {
        parent->child[j + 1] = parent->child[j];
    }

    parent->child[index + 1] = new_knot;

    for (int j = parent->size - 1; j >= index; j--) {
        parent->arr[j + 1] = parent->arr[j];
    }

    parent->arr[index] = child->arr[EXT - 1];
    parent->size++;
}

item* create_item(char *key, unsigned info) {
    item *new_item = (item*)malloc(sizeof(item));
    if (new_item == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_item->key = strdup(key);
    new_item->head = create_node(info);
    return new_item;
}

void insert_non_full(knot *root, char *key, unsigned info) {
    int i = root->size - 1;

    if (root->child[0] == NULL) {
        while (i >= 0 && strcmp(root->arr[i]->key, key) > 0) {
            root->arr[i + 1] = root->arr[i];
            i--;
        }

        if (i >= 0 && strcmp(root->arr[i]->key, key) == 0) {

            node *current = root->arr[i]->head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = create_node(info);
        } else {
            root->arr[i + 1] = create_item(key, info);
            root->size++;
        }
    } else {
        while (i >= 0 && strcmp(root->arr[i]->key, key) > 0) {
            i--;
        }

        i++;

        if (root->child[i]->size == 2 * EXT - 1) {
            split_child(root, i, root->child[i]);

            if (strcmp(root->arr[i]->key, key) < 0) {
                i++;
            }
        }

        insert_non_full(root->child[i], key, info);
    }
}


void print_item_search(item *element, int version) {
    if (element == NULL) {
        printf("Элемент не найден.\n");
        return;
    }

    node *current = element->head;
    int count = 1;


    while (current != NULL && count < version) {
        current = current->next;
        count++;
    }

    if (current != NULL && count == version) {
        printf("Ключ: %s, Версия: %d, Информация: %u\n", element->key, version, current->info);
    } else {
        printf("Версия %d для ключа %s не найдена.\n", version, element->key);
    }
}


void print_knot_screen(const char* prefix, const knot* node, int isLeft) {
    if (node != NULL) {
        printf("%s", prefix);

        printf("%s", (isLeft ? "├──" : "└──"));


        for (int i = 0; i < node->size; i++) {
            printf("%s", node->arr[i]->key);
            if (i < node->size - 1) {
                printf("-");
            }
        }

        printf("\n");

        for (int i = 0; i <= node->size; i++) {
            char newPrefix[1000];
            snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, (isLeft ? "│   " : "    "));
            print_knot_screen(newPrefix, node->child[i], i < node->size);
        }
    }
}

int get_releases(item *list)
{
	node *ptr = list->head;
	int cnt = 0;
	while (ptr != NULL)
	{
		++cnt;
		ptr = ptr->next;
	}
	return cnt;
}

int remove_tree(tree *tr, char *key)
{
	process_tree(tr);
	knot *ptr = tr->root;
	while (!knot_is_sheet(ptr))
	{
		int index = choose_index(ptr, key);

		if (index != 2 * EXT - 1 && ptr->arr[index] != NULL && strcmp(key, ptr->arr[index]->key) == 0) {
			ptr = process2(ptr, index);
		} else {

			ptr = process1(ptr, index);
		}
	}
	int index = knot_contains(ptr, key);
	if (index != -1)
	{
		remove_item(ptr, index);
		return 1;
	}
	return 0;
}