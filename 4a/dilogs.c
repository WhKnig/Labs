#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "vvod.h"
#include "dilogs.h"
#include <readline/readline.h>

int dilog_3_in(tree *tr, char *key)
{
    int fl = 0;
    key = get_key();
    if(key == NULL){return -1;}
    unsigned info = get_info(&fl);
    if(fl == -1){free(key);return -1;}
    fl = insert(tr, key, info);
    if(fl == -1){free(key); return -1;}
    free(key);
    return fl;
}

int dilog_2(tree *tr, char *key)
{
    key = readline("Введите key: ");
    if(key == NULL){free(key);return -1;}
    obhod(tr, key);
    free(key);
    return 0;
}

int dilog_4_k(tree *tr, char *key)
{
    int fl = 0;
    key = get_key();
    if(key == NULL){free(key);key = NULL;return -1;}
    fl = delete_k(tr, key);
    if(fl == 1){printf("Нет такого!\n");} 
    free(key);
    key = NULL;
    return fl;
}

int dilog_5(tree *tr, char *key)
{
    int fl = 0, ver = 0;
    node *res = NULL;
    key = get_key();
    if(key == NULL){free(key);key = NULL;return -1;}
    printf("Введите версию: "); 
    fl = scanf("%d", &ver);
    while (fl != 1 || ver < 1)
    {
        if(fl == -1){return -1;}
        printf("\n");
        scanf("%*[^\n]");
        printf("Введите версию: ");  
        fl = scanf("%d", &ver);
    }

    res = poisk(tr, key, ver);
    if(res != NULL){printf("№%d %s: %u\n", ver, res->key, res->info);}else{printf("Нет такого!\n");}
    free(key);
    key = NULL;
    return fl;
}

int dilog_6(tree *tr, char *key)
{
    int fl = 0, ver = 0;
    node *res = NULL;
    key = get_key();
    if(key == NULL){free(key);key = NULL;return -1;}
    printf("Введите версию: "); 
    fl = scanf("%d", &ver);
    while (fl != 1 || ver < 1)
    {
        if(fl == -1){return -1;}
        printf("\n");
        scanf("%*[^\n]");
        printf("Введите версию: ");  
        fl = scanf("%d", &ver);
    }
    res = sp_search(tr, key, ver);
    if(res != NULL){printf("№%d %s: %u\n", ver, res->key, res->info);}else{printf("Нет такого!\n");}
    free(key);
    key = NULL;
    return fl;
}

int dilog_7(tree *tr)
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
                    insert(tr, nodes[i].key, nodes[i].info);
                }
                clock_gettime(CLOCK_MONOTONIC, &end);
                f_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                printf("    'insert' is: %.8f sec\n", f_time);
                break;
            case 2:
                if(dfl != 1){printf("   Сначало призведите вставку!\n");break;}
                clock_gettime(CLOCK_MONOTONIC, &start);
                for(int i = 0; i < n; i++)
                {
                    delete_k(tr, nodes[i].key);

                }
                
                clock_gettime(CLOCK_MONOTONIC, &end);
                f_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                printf("    'delete_k' is: %.8f sec\n", f_time);
                dfl = 0;
                break;
            case 3:
                if(dfl != 1){printf("   Сначало призведите вставку!\n");break;}
                clock_gettime(CLOCK_MONOTONIC, &start);
                for(int i = 0; i < n; i++)
                {
                    
                    poisk(tr, nodes[i].key, 1);
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