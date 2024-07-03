#include <stdio.h>
#include <stdlib.h>
#include "tabl.h"
#include "vvod.h"
#include "dilogs.h"

int dilog_3_in(Table *map, char *key, char *info)
{
    int fl = 0;
    key = get_key();
    if(key == NULL){free(key);key = NULL;return -1;}
    info = get_info();
    if(info == NULL){free(key);free(info);key = NULL;info = NULL;return -1;}
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
    if(map->csize != 0){(*new) = nashli(map, key);
    if((*new) == NULL){(*chn) = 0;}else{posmotrim((*new));}}else{printf("Таблица пуста\n");}
    free(key);
    return 0;
}

int dilog_4_kv(Table *map, char *key)
{
    int fl = 0, v = 0;
    key = get_key();
    if(key == NULL){free(key);key = NULL;return -1;}
    fl = vers_in(&v);
    if(fl != 0){return -1;}
    fl = delete_kv(map, key, v);
    free(key);
    key = NULL;
    return fl;
}

int dilog_5_k(Table *map, char *key)
{
    int fl = 0;
    key = get_key();
    if(key == NULL){free(key); key = NULL; return -1;}
    fl = delete_k(map, key);
    free(key);
    key = NULL;
    return fl;
}

