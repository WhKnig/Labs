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

char* get_info()
{
    char *info = readline("Введите info: ");
    if(info == NULL){return NULL;}
    while(strlen(info) == 0)
    {
        free(info);
        info = NULL;
        info = readline("Введите info: ");
        if(info == NULL){return NULL;}
    }
    
    return info;
}

int menu(int *n)
{
    printf("1 - Вставка новго элемента\n");
    printf("2 - Удалене из таблицы элемента\n");
    printf("3 - Поиск в таблице по ключу\n");
    printf("4 - Вывод таблицы\n");
    printf("5 - Импорт из TXT\n");
    printf("6 - Удаление из таблицы всех версий элемента\n");
    printf("7 - Реорганизация таблицы\n");
    printf("8 - Создание таблицы\n");
    printf("9 - Завершить\n");
    printf("10 - Вывод таблицы из пункта 3\n");
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


int vers_in(int *n)
{
    scanf("%*[^\n]");
    printf("Введите версию: ");
    int fl = scanf("%d", n);
    while (fl != 1 || (*n) <= 0)
    {
        if(fl == -1){return fl;}
        printf("\n");
        printf("Введите версию: ");
        fl = scanf("%d", n);
            
    }
    return 0;

}
