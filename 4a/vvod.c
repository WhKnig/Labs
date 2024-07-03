#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "vvod.h"
#include <readline/readline.h>

char* get_key()
{
    char *key = readline("Введите key: ");
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

unsigned get_info(int *fl)
{
    (*fl) = 0;
    unsigned n = 0;
    printf("Введите info: ");
    int f = scanf("%u", &n);
    while (f != 1)
    {
        if(f == -1){(*fl) = -1;break;}
        printf("\n"); 
        scanf("%*[^\n]");
        printf("Введите info: ");
        f = scanf("%u", &n);
    }
    return n;
}

int menu(int *n)
{
    printf("1 - Вставка новго элемента\n");
    printf("2 - Удалене элемента\n");
    printf("3 - Поиск по ключу\n");
    printf("4 - Форматированный вывод\n");
    printf("5 - Импорт из TXT\n");
    printf("6 - Вывод графически\n");
    printf("7 - Обход\n");
    printf("8 - Специальный поиск\n");
    printf("9 - Генератор дерева\n");
    printf("10 - Генератор массива для ввода\n");
    printf("11 - Тестирование\n");
    printf("12 - Завершить\n");
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

int menu_test(int *n)
{
    printf("    1 - Вставка\n");
    printf("    2 - Удалене\n");
    printf("    3 - Поиск\n");
    printf("    4 - Завершить\n");
    printf("    >> ");
    int fl = scanf("%d", n);
    while (fl != 1 || ((*n) < 1 || (*n) > 5))
    {
        if(fl == -1){(*n) = -1;break;}
        printf("\n");
        scanf("%*[^\n]");
        printf("    >> ");  
        fl = scanf("%d", n);
            
    }
    return fl;
}



