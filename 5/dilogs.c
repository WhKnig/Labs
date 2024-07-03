#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "vvod.h"
#include "dilogs.h"
#include <readline/readline.h>

int dialog_dob_ver(Graf *graf)
{
    int fl = 0;
    char *name = get_name();
    if(name == NULL){free(name); return -1;}
    unsigned port = get_port(&fl);
    if(fl == -1){free(name); return -1;}
    fl = add_vertex(graf, name, port);
    if(fl == 1){printf("Есть такое!\n");}
    free(name);
    return 0;
}

int dialog_dob_rebr(Graf *graf)
{
    int fl = 0;
    char *v1 = NULL, *v2 = NULL;
    printf("1 вершина:");
    v1 = get_name();
    if(v1 == NULL){free(v1);return -1;}
    printf("2 вершина:");
    v2 = get_name();
    if(v1 == NULL){free(v2);free(v1);return -1;}
    printf("Колличество портов:");
    unsigned len = 0;
    int f = scanf("%u", &len);
    while (f != 1)
    {
        if(fl == -1){free(v2);free(v1);return -1;}
        printf("\n"); 
        scanf("%*[^\n]");
        printf("Колличество портов:");
        f = scanf("%u", &len);
    }
    
    printf("Ввод портов в массив ограничений:\n");
    unsigned port;
    unsigned *ports = calloc(len, sizeof(unsigned));
    for(int i = 0; i < len; i++)
    {
        port = get_port(&fl);
        if(fl == -1){free(v2);free(v1);free(ports);return -1;};
        ports[i] = port;
    }
    fl = add_edge(graf, ports, len, v1, v2);
    if(fl == 1){printf("Нет вершин(ы)!\n");};
    free(v1);
    free(v2);
    free(ports);
    return 0;
}

int dialog_del_ver(Graf *graf)
{
    int fl = 0;
    char *name = get_name();
    if(name == NULL){free(name); return -1;}
    fl = del_vertex(graf, name);
    if(fl == 1){printf("Ошибка!\n");}
    free(name);
    return 0;
}

int dialog_del_rebr(Graf *graf)
{
    int fl = 0;
    char *v1 = NULL, *v2 = NULL;
    printf("1 вершина:");
    v1 = get_name();
    if(v1 == NULL){free(v1);return -1;}
    printf("2 вершина:");
    v2 = get_name();
    if(v1 == NULL){free(v2);free(v1);return -1;}
    fl = del_edge(graf, v1, v2);
    if(fl == 1){printf("Ошибка!\n");}
    free(v1);
    free(v2);
    return 0;
}

int dialog_ex_ver(Graf *graf)
{
    int fl = 0, n = 0;
    char *v1 = get_name();
    if(v1 == NULL){free(v1); return -1;}
    printf("1 - Изменить имя\n");
    printf("2 - Изменить порт\n");
    printf(">> "); 
    fl = scanf("%d", &n);
    while (fl != 1 || (n< 1 || n > 2))
    {
        if(fl == -1){free(v1);return -1;}
        printf("\n");
        scanf("%*[^\n]");
        printf(">> ");  
        fl = scanf("%d", &n);
    }

    if(n == 1)
    {
        printf("Новое имя:");
        char *v2 = get_name();
        if(v2 == NULL){free(v1);free(v2); return -1;}
        fl = change_vertex_name(graf, v1, v2);
        if(fl == 1){printf("Ошибка!\n");}
        free(v1);
        free(v2);
        return 0;
    }
    else{
        printf("Новый порт:");
        unsigned port = get_port(&fl);
        if(fl == -1){free(v1);return -1;}
        fl = change_vertex_port(graf, v1, port);
        if(fl == 1){printf("Ошибка!\n");}
        free(v1);
        return 0;
    }
}

int dialog_ex_rebr(Graf *graf)
{
    int fl = 0;
    char *v1 = NULL, *v2 = NULL;
    printf("1 вершина:");
    v1 = get_name();
    if(v1 == NULL){free(v1);return -1;}
    printf("2 вершина:");
    v2 = get_name();
    if(v1 == NULL){free(v2);free(v1);return -1;}
    printf("Новое колличество портов:");
    unsigned len = 0;
    int f = scanf("%u", &len);
    while (f != 1)
    {
        if(fl == -1){free(v2);free(v1);return -1;}
        printf("\n"); 
        scanf("%*[^\n]");
        printf("Новое колличество портов:");
        f = scanf("%u", &len);
    }
    
    printf("Ввод новых портов в массив ограничений:\n");
    unsigned port;
    unsigned *ports = calloc(len, sizeof(unsigned));
    for(int i = 0; i < len; i++)
    {
        port = get_port(&fl);
        if(fl == -1){free(v2);free(v1);free(ports);return -1;};
        ports[i] = port;
    }
    fl = change_edge_ports(graf, v1, v2, ports, len);
    if(fl == 1){printf("Ошибка!\n");}
    free(v1);
    free(v2);
    free(ports);
    return 0;
}

int dialog_obhod(Graf *graf)
{
    int fl = 0;
    printf("Стартовая вершина:");
    char *name = get_name();
    if(name == NULL){free(name); return -1;}
    printf("Целевой порт:");
    unsigned port = get_port(&fl);
    if(fl == -1){free(name);return -1;}
    fl = obhod(graf, name, port);
    if(fl == 1){printf("Ошибка!\n");}
    free(name);
    return 0;
}

int dialog_b_f(Graf *graf)
{
    int fl = 0;
    char *v1 = NULL, *v2 = NULL;
    printf("Стартовая вершина:");
    v1 = get_name();
    if(v1 == NULL){free(v1);return -1;}
    printf("Коечная вершина:");
    v2 = get_name();
    if(v1 == NULL){free(v2);free(v1);return -1;}
    fl = bellman_ford(graf, v1, v2);
    if(fl == 1){printf("Ошибка!\n");}
    if(fl == 2){printf("Кратчайший путь не найден!\n");}
    free(v1);
    free(v2);
    return 0;
}


int dialog_mst(Graf *graf)
{
    int fl = 0;
    unsigned port = get_port(&fl);
    if(fl == -1){return -1;}
    fl = mst(graf, port);
    if(fl == 1){printf("Составить дерево не удалось!\n");}
    return 0;
}