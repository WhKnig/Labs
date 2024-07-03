#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vvod.h"
#include <readline/readline.h>

char* get_name()
{
    char *key = readline("Введите name: ");
    if(key == NULL){return NULL;}
    while(strlen(key) == 0)
    {
        free(key);
        key = NULL;
        key = readline("Введите key: ");
        if(key == NULL){return NULL;}
    }
    return key;
}

unsigned get_port(int *fl)
{
    (*fl) = 0;
    unsigned n = 0;
    printf("Введите port: ");
    int f = scanf("%u", &n);
    while (f != 1)
    {
        if(f == -1){(*fl) = -1;break;}
        printf("\n"); 
        scanf("%*[^\n]");
        printf("Введите port: ");
        f = scanf("%u", &n);
    }
    return n;
}

int menu(int *n)
{
    printf("1 - Инициалзация графа\n");
    printf("2 - Добав вершины\n");
    printf("3 - Добав ребра\n");
    printf("4 - Удаление ребра\n");
    printf("5 - Удаление вершины\n");
    printf("6 - Изменение вершины\n");
    printf("7 - Измеение ребра\n");
    printf("8 - Вывод в виде списка\n");
    printf("9 - Графический вывод\n");
    printf("10 - Обход\n");
    printf("11 - Б-Ф\n");
    printf("12 - Минимальное дерево\n");
    printf("13 - Завершить\n");
    printf(">> ");
    int fl = scanf("%d", n);
    while (fl != 1 || ((*n) < 1 || (*n) > 13))
    {
        if(fl == -1){(*n) = -1;break;}
        printf("\n");
        scanf("%*[^\n]");
        printf(">> ");  
        fl = scanf("%d", n);
            
    }
    return fl;
}


