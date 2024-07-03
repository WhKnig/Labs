#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "vvod.h"
#include "dilogs.h"
#include <readline/readline.h>
#include "func.h"

int dilog_insert(tree *tr, char *key) {
    int fl = 0;
    key = get_key();
    if (key == NULL) { 
        free(key); 
        key = NULL; 
        return -1; 
    }
    unsigned info = get_info(&fl);
    if (fl == -1) { 
        free(key); 
        return -1; 
    }
    fl = insert_tree(tr, key, info);
    if (fl == -1) { 
        free(key); 
        return -1; 
    }
    free(key);
    return fl;
}

int dilog_detour(tree *tr) {

    printf("начальный - ");
    char *low = get_key();
    if (low == NULL) { 
        free(low); 
        return -1; 
    }
    printf("конечный - ");
    char *high = get_key();
     if (high == NULL) { 
        free(low); 
        free(high);
        return -1; 
    }
    printf("Обход:\n");
    int found = 0;
    inorder_traversal(tr->root, low, high, &found);
    if (found == 0) {
        printf("No elements found in the given range\n");
    }
    free(low);
    free(high);
    return 1;
}

int dilog_delete(tree *tr, char *key) {
    int fl = 0;
    key = get_key();
    if (key == NULL) { 
        free(key); 
        key = NULL; 
        return -1; 
    }
    int ver = 0;
    printf("Введите версию: ");
    fl = scanf("%d", &ver);
    while (fl != 1 || ver < 1) {
        if (fl == -1) { 
            return -1; 
        }
        printf("\n");
        scanf("%*[^\n]");
        printf("Введите версию: ");
        fl = scanf("%d", &ver);
    }
    
    fl = delete_version(tr, key, ver);
    if(fl == 1)
    {
         printf("Версия %d для ключа %s не найдена\n", ver, key);
    }
    free(key);
    return 0;
}

int dilog_search(tree *tr, char *key) {
    int ver = 0;
    key = get_key();
    if (key == NULL) { 
        free(key); 
        key = NULL; 
        return -1; 
    }

    printf("Введите версию: ");
    int fl = scanf("%d", &ver);
    while (fl != 1 || ver < 1) {
        if (fl == -1) { 
            return -1; 
        }
        printf("\n");
        scanf("%*[^\n]");
        printf("Введите версию: ");
        fl = scanf("%d", &ver);
    }

    item *element = search_version(tr->root, key, ver);
    if (element != NULL) {
        print_item_search(element, ver);
    } else {
        printf("Нет такого элемента с версией %d!\n", ver);
    }

    free(key);
    return 0;
}

int dilog_sp_search(tree *tr, char *key) {
    key = get_key();
    if (key == NULL) { 
        free(key); 
        key = NULL; 
        return -1; 
    }

    int found = 0;
    item *result = search_max_leq_key(tr->root, key, &found);
    if (!found) {
        printf("Нет никаких элементов, отличающихся от этого\n");
        free(key);
        return 0;
    }

    printf("The element with max key <= '%s' is: %s\n", key, result->key);
    free(key);
    return 1;
}

int dilog_test(tree *tr)
{
    int n;
    printf("Введите колличество узлов: "); 
    int fl = scanf("%d", &n);
    while (fl != 1 || n < 1)
    {
        if(fl == -1){return -1;}
        printf("\n");
        scanf("%*[^\n]");
        printf("Введите колличество узлов: ");  
        fl = scanf("%d", &n);
    }

    gen_tree(tr, n);

    return 0;
}

int testing(tree *tr, gnode *nodes, int n)
{
    int ending = 0, fl = 0, dfl = 0;
    struct timespec start, end;
    double f_time = 0.0;

    while(ending != -1)
    {
        fl = menu_test(&ending);
        if(fl == -1){return -1;}
        f_time = 0;

        switch (ending)
        {
            case 1:
                dfl = 1;
                clock_gettime(CLOCK_MONOTONIC, &start);
                for(int i = 0; i < n; i++)
                {
                    insert_tree(tr, nodes[i].key, nodes[i].info);
                }
                clock_gettime(CLOCK_MONOTONIC, &end);
                f_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                printf("    'insert' is: %.8f sec\n", f_time);
                break;
            case 3:
                if(dfl != 1){printf("   Сначало призведите вставку!\n");break;}
                clock_gettime(CLOCK_MONOTONIC, &start);
                for(int i = 0; i < n; i++)
                {
                    delete_version(tr, nodes[i].key, 1);

                }
                
                clock_gettime(CLOCK_MONOTONIC, &end);
                f_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                printf("    'delete_k' is: %.8f sec\n", f_time);
                dfl = 0;
                break;
            case 2:
                if(dfl != 1){printf("   Сначало призведите вставку!\n");break;}
                clock_gettime(CLOCK_MONOTONIC, &start);
                for(int i = 0; i < n; i++)
                {
                    
                    search_version(tr->root, nodes[i].key, 1);
                }
                clock_gettime(CLOCK_MONOTONIC, &end);
                f_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                printf("    'poisk' is: %.8f sec\n", f_time);
                break;
            case 4:
                ending = -1;
                break;
            default:
                break;
        }

    }
    return 0;
}