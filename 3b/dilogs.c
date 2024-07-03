#include <stdio.h>
#include <stdlib.h>
#include "tabl.h"
#include "vvod.h"
#include "dilogs.h"

int dilog_3_in(Table *map, char *key)
{
    int fl = 0;
    if(map->csize == map->msize){printf("Нет свободных ячеек!\n"); return fl;}
    key = get_key();
    if(key == NULL){free(key);key = NULL;return -1;}
    unsigned info = get_info(&fl);
    if(fl != 0){free(key);key = NULL;return -1;}
    fl = insert(map, key, info);
    return fl;
}

int dilog_1(Table **map, int *ch)
{
    int size = 0, fl = 0;
    
    
    fl = 0;
    scanf("%*[^\n]");
    fl = yach(&size);
    if(fl == -1){return -1;} 
    (*map) = create_map(size);
    if((*map) == NULL){return -1;}
    (*ch) = 1;
    return 0;
}

int dilog_2(Table **new, Table *map, int *chn)
{
    
    char *key = NULL;
    key = get_key();
    if(key == NULL){(*chn) = 0;free(key);key = NULL;return -1;}
    (*chn) = 1;
    (*new) = nashli(map, key);
    if((*new) == NULL){(*chn) = 0;}else{posmotrim((*new));}
    free(key);
    return 0;
}

int dilog_4_k(Table *map, char *key)
{
    int fl = 0;
    key = get_key();
    if(key == NULL){free(key);key = NULL;return -1;}
    fl = delete_k(map, key);
    free(key);
    key = NULL;
    return fl;
}