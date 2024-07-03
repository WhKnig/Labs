#include <stdio.h>
#include <stdlib.h>
#include "tabl.h"
#include <string.h>
#include "vvod.h"
#include <string.h>


Table* create_map(int size)
{
    Table *map = (Table*)malloc(1 * sizeof(Table));
    
    map->msize = size;
    map->ks = (KeySpace*)calloc(size, sizeof(KeySpace));
    map->csize = 0;
    return map;
}


int insert(Table *map, char *key, char *info)
{
    int nrel = 0, n = -1;
    for(int i = (map->csize-1); i >= 0; i--)
    {
        if(map->ks[i].busy == 1 && strcmp(map->ks[i].key, key) == 0)
        {
            nrel = map->ks[i].release;
            break;
        }
    }

    if(map->csize == map->msize){reorganize(map);}

    if(map->csize <= map->msize)
    {
        if(map->csize < map->msize && map->ks[map->csize].busy == 0){n = map->csize;}
        if(n == -1){
            if(map->csize == map->msize)
            {
                if(map->ks[map->csize-1].busy == 0){map->csize--;n = map->csize;}
            }
        }
        
    }
    if(n == -1)
    {
        printf("Нет свободных ячеек!\n");
        free(key);
        key = NULL;
        free(info);
        info = NULL;
        return 0;
    }

    if(map->ks[n].key != NULL){free(map->ks[n].key);}
    map->ks[n].key = key;
    if(map->ks[n].info != NULL){free(map->ks[n].info);}
    map->ks[n].info = info;
    map->ks[n].busy = 1;
    map->ks[n].release = nrel + 1;
    map->csize++;
    return 0;
}

int delete_k(Table *map, char *key)
{
    int flk = 0;
    for(int i = 0; i < map->csize; i++)
    {
        if(strcmp(key, map->ks[i].key) == 0 && map->ks[i].busy == 1)
        {
            flk = 1;
            map->ks[i].busy = 0;
        }
    }

    if(flk != 1)
    {
        printf("Элементы с заданным ключём не найден\n");
    }
    return 0;
}

int delete_kv(Table *map, char *key, int v)
{
    int flk = 0, flv = 0;
    for(int i = 0; i < map->csize; i++)
    {
        if(strcmp(map->ks[i].key, key) == 0 && map->ks[i].busy == 1)
        {
            flk++;
            if(map->ks[i].release == v)
            {
                flv++;
                map->ks[i].busy = 0;
                break;
            }

        }
    }

    if(flk == 0)
    {
        printf("Элемент с заданным ключём не найден\n");
    }

    if(flv == 0)
    {
        printf("Элемент с заданной версией не найден\n");
    }
    return 0;
}

void posmotrim(const Table *map)
{
    int f = 0;
    printf("Индекс\tКлюч\tВерсия\tInfo\tСостаяние\n");
    for(int i = 0; i < map->csize; i++)
    {
        if(map->ks[i].busy == 1)
        {
            printf("%d\t", i);
            printf("%s\t", map->ks[i].key);
            printf("%d\t", map->ks[i].release);
            printf("%s\t", map->ks[i].info);
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
        if(map->ks[i].info != NULL){free(map->ks[i].info);}
    }
    free(map->ks);
    free(map);
}

void reorganize(Table *map)
{
    int z = -1, p = -1, sch = 0;
    for(int i = 0;  i < map->csize; i++)
    {
        if(map->ks[i].busy == 0 && p == -1){p = i;}
        if(map->ks[i].busy == 1 && (p != -1 && z == -1)){z = i;}
        if(p != -1 && z != -1)
        {
            KeySpace temp = map->ks[p];
            map->ks[p] = map->ks[z];
            map->ks[z] = temp;
            i = p;
            p = -1;
            z = -1;

        }
        if(map->ks[i].busy == 1){sch++;}
    }
    if(sch != 0){map->csize = sch;}
}





Table* nashli(const Table *map, char *key)//добавить элемент
{
    int flk = 0;

    Table *new = (Table*)calloc(1, sizeof(Table));
    new->ks = (KeySpace*)calloc(1, sizeof(KeySpace));
  
    for(int i = 0; i < map->csize; i++)
    {
        if(strcmp(map->ks[i].key, key) == 0 && map->ks[i].busy == 1)
        {
            flk++;
            if(flk > 1){new->ks = realloc(new->ks, flk * sizeof(KeySpace));}
            
            new->ks[flk-1].key = strdup(map->ks[i].key);
            new->ks[flk-1].info = strdup(map->ks[i].info);
            new->ks[flk-1].busy = map->ks[i].busy;
            new->ks[flk-1].release = map->ks[i].release;

        }
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
