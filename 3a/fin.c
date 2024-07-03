// #include "txt.h"
// #include "inpp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "tabl.h"
// #include "fin.h"




char* fline(FILE *file) 
{
    int j = 0, cn = 10, f = 0, d = 0;
    char *vivd = (char*)malloc(cn * sizeof(char));
    char m[11]; 
    fscanf(file, "%*[\n]");
    
    while (f == 0) {
        for (int i = 0; i < 10; i++) {
            m[i] = 0;
        }

        d = fscanf(file, "%10[^\n]", m);
        if (d == EOF) {
            free(vivd);
            return NULL;
        } else if (d == 0) {
            f = 1;
            vivd = (char*)realloc(vivd, (j + 1) * sizeof(char));
        } else if (d == 1) {
            for (int i = 0; i < 10; i++) {
                if (m[i] != 0) {
                    vivd[j] = m[i];
                    j++;
                } else {
                    break;
                }
            }
            cn = cn + 10;
            vivd = (char*)realloc(vivd, cn * sizeof(char));
        }
    }

    vivd[j] = '\0';
    return vivd;
}

Table* f_in(int *f)
{
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
    int flag = fscanf(file, "%d", &n);
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
    Table *map = create_map(n);
    // map->ks = (KeySpace*)calloc(n, sizeof(KeySpace));
    // map->msize = n;

    for (int i = 0; i < n; i++)
    {
        // printf("ops");
        char *key = fline(file);
        char *info = fline(file);
        if(key == NULL || info == NULL){if(i == 0){freak(map);printf("Таблица пустая\n");return NULL;}free(key);free(info);return map;}
        // printf("%s ", key);
        // printf("%s\n", info);
        map->ks[i].key = key;
        map->ks[i].info = info;
        // printf("%s\n", map->ks[i].key);

        int m = 0;
        for(int j = 0; j < map->csize; j++)
        {
            if(strcmp(map->ks[i].key, map->ks[j].key) == 0 && map->ks[j].busy != 0)
            {
                if(m < map->ks[j].release)
                {
                    m = map->ks[j].release;
                }
            }
        }
        map->ks[i].release = m + 1;
        map->ks[i].busy = 1;
        map->csize++;
        fscanf(file, "%*[\n]");
    }
    fclose(file);
    return map;
}