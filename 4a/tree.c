#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int insert(tree *tr, char *key, unsigned info) 
{
    if (tr->head == NULL) {
        tr->head = (node*)malloc(sizeof(node));
        tr->head->key = strdup(key);
        tr->head->info = info;
        tr->head->left = NULL;
        tr->head->right = NULL;
        return 0;
    }

    node *current = tr->head;
    node *parent = NULL;
    while (current != NULL) {
        parent = current;
        if (strcmp(key, current->key) <= 0)
            current = current->left;
        else
            current = current->right;
    }

    node *newNode = (node*)malloc(sizeof(node));
    newNode->key = strdup(key);
    newNode->info = info;
    newNode->left = NULL;
    newNode->right = NULL;

    if (strcmp(key, parent->key) <= 0)
        parent->left = newNode;
    else
        parent->right = newNode;

    return 0;
}


node* FindMin(node* root) {
    while(root->left != NULL) 
        root = root->left;
    return root;
}

void freeNode(struct node *root) {
    if (root == NULL) return;
    freeNode(root->left);
    freeNode(root->right);
    free(root->key);
    free(root);
}


int delete_k(tree *tr, const char *key) {
    if (tr == NULL || tr->head == NULL) return 1;

    struct node *current = tr->head;
    struct node *parent = NULL;
    while (current != NULL && strcmp(key, current->key) != 0) {
        parent = current;
        if (strcmp(key, current->key) < 0)
            current = current->left;
        else
            current = current->right;
    }

    if(current == NULL){return 1; }

    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL)
            tr->head = NULL;
        else if (parent->left == current)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(current->key);
        free(current);
    }
    else if (current->left == NULL) {
        if (parent == NULL)
            tr->head = current->right;
        else if (parent->left == current)
            parent->left = current->right;
        else
            parent->right = current->right;
        free(current->key);
        free(current);
    } else if (current->right == NULL) {
        if (parent == NULL)
            tr->head = current->left;
        else if (parent->left == current)
            parent->left = current->left;
        else
            parent->right = current->left;
        free(current->key);
        free(current);
    }
    
    else {
        struct node *temp = FindMin(current->right);
        free(current->key);
        current->key = strdup(temp->key);
        if (temp == current->right) {
            current->right = temp->right;
        } else {
            struct node *temp_parent = current->right;
            while (temp_parent->left != temp) {
                temp_parent = temp_parent->left;
            }
            temp_parent->left = temp->right;
        }
        free(temp->key);
        free(temp);
    }
    return 0;
}




void printBT(const char *prefix, const node *root, int isLeft) {
    if (root != NULL) {
        printf("%s%s(%s, %u)\n", prefix, (isLeft ? "├──" : "└──"), root->key, root->info);

        
        char leftPrefix[255];
        snprintf(leftPrefix, sizeof(leftPrefix), "%s%s", prefix, (isLeft ? "│   " : "    "));
        printBT(leftPrefix, root->left, 1);

        leftPrefix[strlen(prefix)] = '\0';

        char rightPrefix[255];
        snprintf(rightPrefix, sizeof(rightPrefix), "%s%s", prefix, (isLeft ? "│   " : "    "));
        printBT(rightPrefix, root->right, 0);

        rightPrefix[strlen(prefix)] = '\0';
    }
}

void printBinaryTree(const tree *tr) {
    printBT("", tr->head, 0);
}

void freenode(node *root) {
    if (root != NULL) {
        freeNode(root->left);
        freeNode(root->right);
        free(root->key);
        free(root);
    }
}

void freeTree(tree *tr) {
    if (tr != NULL && tr->head != NULL) {
        freenode(tr->head);
        
        free(tr);
    }
}

void reverse_inorder(node *root) {
    if (root == NULL) {
        return;
    }
    reverse_inorder(root->right);
    
    printf("%s (%u)\n", root->key, root->info);

    reverse_inorder(root->left);
}



void reverse_in(node *root, const char *key) {
    if (root == NULL)
        return;

    reverse_in(root->right, key);

    if (key == NULL || strcmp(root->key, key) > 0) {
        printf("(%s, %u)\n", root->key, root->info);
    }

    reverse_in(root->left, key);
}

void obhod(const tree *tr, const char *key) {
    if (tr == NULL || tr->head == NULL)
        return;
    if(strlen(key) != 0)
    {reverse_in(tr->head, key);}
    else{reverse_inorder(tr->head);}
}

void reverse_inorder_t(node *root) {
    if (root == NULL) {
        return;
    }

    reverse_inorder(root->right);
    
    
    reverse_inorder(root->left);
}



void reverse_in_t(node *root, const char *key) {
    if (root == NULL)
        return;

    reverse_in_t(root->right, key);

    reverse_in_t(root->left, key);
}

void obhod_test(const tree *tr, const char *key) {
    if (tr == NULL || tr->head == NULL)
        return;
    if(strlen(key) != 0)
    {reverse_in_t(tr->head, key);}
    else{reverse_inorder_t(tr->head);}
}

node* poisk(const tree *tr, const char *key, int ver) 
{
    node *current = tr->head;
    int n = 0;
    while (current != NULL) {
        int cmp = strcmp(key, current->key);
        if (cmp == 0) {
            n++;
            if(n == ver){return current;}
            current = current->left;
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if(n == 0){return NULL;}
    return 0;
}

node* sp_search(const tree *tr, const char *key, int ver) 
{

    node *result = NULL;
    node *temp = tr->head;
    while (temp != NULL) {
        if (strcmp(key, temp->key) >= 0) {
            temp = temp->right;
        } else {
            
            if(result != NULL)
            {
                if(strcmp(temp->key, result->key) >= 0){break;}
            }
            result = temp;
            temp = temp->left;
        }
    }
    if(result == NULL){return NULL;}

    temp = poisk(tr, result->key, ver);
 
    return temp;
}

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

