#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabl.h"
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
    printf("2 - Удалене из таблицы элемента\n");
    printf("3 - Поиск в таблице по ключу\n");
    printf("4 - Вывод таблицы\n");
    printf("5 - Импорт из BIN\n");
    printf("6 - Экспорт в BIN\n");
    printf("7 - Создание таблицы\n");
    printf("8 - Завершить\n");
    printf("9 - Вывод таблицы из пункта 3\n");
    printf(">> ");
    int fl = scanf("%d", n);
    while (fl != 1 || ((*n) < 1 || (*n) > 10))
    {
        if(fl == -1){(*n) = -1;break;}
        printf("\n");
        scanf("%*[^\n]");
        printf(">> ");  
        fl = scanf("%d", n);
            
    }
    return fl;
}

int yach(int *n)
{
    printf("Введите количество ячеек: ");
    int fl = scanf("%d", n);
    while (fl != 1 || (*n) <= 0)
    {
        if(fl == -1){(*n) = -1;break;}
        printf("\n"); 
        scanf("%*[^\n]");
        printf("Введите количество ячеек: ");
        fl = scanf("%d", n);
    }
    return fl;
}
