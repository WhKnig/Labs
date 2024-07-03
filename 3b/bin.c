// #include "txt.h"
// #include "inpp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "tabl.h"

int check_dub(const Table *map, char *key, int m)
{
    for(int i = 0; i < m; i++)
    {
        if(map->ks[i].busy != 0 && strcmp(key, map->ks[i].key) == 0)
        {
            return 1;
        }
    }
    return 0;
}


int b_out(Table *map)
{
    char *filename = readline("Input out-filename: ");
    if(filename == NULL){return -1;}
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file");
        free(filename);
        return 1;
    }
    free(filename);

    fwrite(&map->msize, sizeof(int), 1, file);
    char nul = '\0';  

    for (int i = 0; i < map->msize; i++)
    {
        fwrite(&map->ks[i].busy, sizeof(int), 1, file);
        fwrite(&nul, sizeof(char), 1, file);
        if(map->ks[i].busy == 0){ continue;}
        int l =  strlen(map->ks[i].key);
        fwrite(&l, sizeof(int), 1, file);
        fwrite(&nul, sizeof(char), 1, file);
        fwrite(map->ks[i].key, sizeof(char), strlen(map->ks[i].key), file);
        fwrite(&nul, sizeof(char), 1, file);
        fwrite(&map->ks[i].info, sizeof(unsigned), 1, file);
        fwrite(&nul, sizeof(char), 1, file);
    }
    fclose(file);
    return 0;
}


Table* b_in(int *f) {
    (*f) = 0;
    char *filename = readline("Input filename: ");
    if(filename == NULL){(*f) = 1;return NULL;}
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        free(filename);
        return NULL;
    }
    free(filename);

    
    int n = 0;
    int flag = fread(&n, sizeof(int), 1, file);
    if (n <= 0)
    {
        printf(" %d ... Think about it! ;)\n", n);
        fclose(file);
        return NULL;
    }
    if (flag == -1)
    {
        fclose(file);
        return NULL;
    }
    Table *map = (Table *)calloc(1, sizeof(Table));
    map->msize = n;

    map->ks = (KeySpace *)calloc(map->msize,sizeof(KeySpace));

    char ch;
    int l = 0;

    for (int i = 0; i < map->msize; i++) {
        fread(&map->ks[i].busy, sizeof(int), 1, file);
        fread(&ch, sizeof(char), 1, file); 
        if (map->ks[i].busy == 0) {continue;}
        fread(&l, sizeof(int), 1, file);
        fread(&ch, sizeof(char), 1, file); 

        map->ks[i].key = (char *)calloc(l+1, sizeof(char));
        fread(map->ks[i].key, sizeof(char), l, file);
        map->ks[i].key[l] = '\0'; 
        fread(&ch, sizeof(char), 1, file);
      
        if(strlen(map->ks[i].key) == 0)
        {
            printf("Ключ  не задан\n");
            freak(map);
            return NULL;
        }
        if(check_dub(map, map->ks[i].key, i) != 0)
        {
            printf("Ключи дублируются\n");
            freak(map);
            return NULL;
        }

        fread(&map->ks[i].info, sizeof(unsigned), 1, file);
        fread(&ch, sizeof(char), 1, file); 
    }

    fclose(file);
    return map;
}
