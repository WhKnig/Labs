#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "tree.h"


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

int f_in(tree *tr) {
    char *filename = readline("Input filename: ");
    if (filename == NULL) {
        return -1;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        free(filename);
        return 0;
    }
    free(filename);
    char *key, *info;
    while ((key = fline(file)) != NULL && (info = fline(file)) != NULL) {
        insert(tr, key, strtoul(info, NULL, 10));
        free(key);
        free(info);
    }
    fclose(file);
    return 0;
}