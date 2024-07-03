#include <stdio.h>
#include <stdlib.h>
#include "tabl.h"
#include <string.h>
#include "vvod.h"
#include <string.h>
#include "hash.h"


Table* create_map(int size)
{
    Table *map = (Table*)malloc(1 * sizeof(Table));
    
    map->msize = size;
    map->ks = (KeySpace*)calloc(size, sizeof(KeySpace));
    map->csize = 0;
    return map;
}


int insert(Table *map, char *key, unsigned info)
{
    unsigned n = 0, step = 0;

    get_data(key, map->msize, &step, &n);
    unsigned i = 0;
    unsigned p = 0;

    while(i != map->msize)
    {
        p = (n + i*step)%map->msize;
        if(map->ks[p].busy == 1 && strcmp(key, map->ks[p].key) == 0)
        {
            printf("Ключ уже существует\n");
            free(key);
            key = NULL;

            return 0;
        }

        if(map->ks[p].busy == 0 || map->ks[p].busy == 2)
        {
            break;
        }
        i++;
    }

    if(map->ks[p].key != NULL){free(map->ks[p].key);}
    map->ks[p].key = key;
    map->ks[p].info = info;
    map->ks[p].busy = 1;
    map->csize++;
    return 0;
}

int delete_k(Table *map, char *key)
{
    int flk = 0;
    unsigned n = 0, step = 0;

    get_data(key, map->msize, &step, &n);
    unsigned i = 0;
    unsigned p = 0;

    while(i != map->msize)
    {
        p = (n + i*step)%map->msize;
        if(map->ks[p].busy == 0)
        {
            break;
        }
        if(map->ks[p].busy == 1 && strcmp(key, map->ks[p].key) == 0)
        {
            flk++;
            map->ks[p].busy = 2;
            map->csize--;
            return 0;
        }
        i++;
    }

    if(flk != 1)
    {
        printf("Элементы с заданным ключём не найден\n");
    }
    return 0;
}

void posmotrim(const Table *map)
{
    int f = 0;
    printf("Индекс\tКлюч\tInfo\tСостаяние\n");
    for(int i = 0; i < map->msize; i++)
    {
        if(map->ks[i].busy == 1)
        {
            printf("%d\t", i);
            printf("%s\t", map->ks[i].key);
            printf("%u\t", map->ks[i].info);
            printf("%d\n", map->ks[i].busy);
            f = 1;
        }
    }
    printf("\n");
    if(f != 1)
    {
        printf("Таблица пуста!\n");
    }
}

void spesial_vivod(const Table *map)
{
    int f = 0;
    printf("Индекс\tКлюч\tInfo\tСостаяние\n");
    for(int i = 0; i < map->msize; i++)
    {
        if(map->ks[i].busy != 0)
        {
            printf("%d\t", i);
            printf("%s\t", map->ks[i].key);
            printf("%u\t", map->ks[i].info);
            printf("%d\n", map->ks[i].busy);
            f = 1;
        }
    }
    printf("\n");
    if(f != 1)
    {
        printf("Таблица пуста!\n");
    }
}

void freak(Table *map){

    printf("Очистка\n");
    for(int i = 0; i < map->msize; i++)
    {
        if(map->ks[i].key != NULL){free(map->ks[i].key);}
    }
    free(map->ks);
    free(map);
}


Table* nashli(const Table *map, char *key)
{
    int flk = 0;

    Table *new = (Table*)calloc(1, sizeof(Table));
    new->ks = (KeySpace*)calloc(1, sizeof(KeySpace));
  
    unsigned n = 0, step = 0;

    get_data(key, map->msize, &step, &n);
    unsigned i = 0;
    unsigned p = 0;

    while(i != map->msize)
    {
        p = (n + i*step)%map->msize;
        if(map->ks[p].busy == 0)
        {
            break;
        }
        if(map->ks[p].busy != 0 && strcmp(key, map->ks[p].key) == 0)
        {
            flk++;
            if(flk > 1){new->ks = realloc(new->ks, flk * sizeof(KeySpace));}

            new->ks[flk-1].key = strdup(map->ks[p].key);
            new->ks[flk-1].info = map->ks[p].info;
            new->ks[flk-1].busy = 1;
        }
        i++;
    }
    
    new->csize = flk;
    new->msize = flk;

    if(flk == 0)
    {
        printf("Нет ткого ключа\n");
        freak(new);
        new = NULL;
        return NULL;
    }

    return new;
}
