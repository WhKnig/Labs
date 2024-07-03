#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include <readline/readline.h>
#include <string.h>
#include "in.h"
#include "mstring.h"

void ochit(sector *a, int f)
{
    if(f == 0){printf("Ошибка формата!\n");}
    free(a->v);
    free(a);

}

void ochist_ch(sector *a, int f)
{
    for(int i = 0; i < f; i++)
    {
        if(a->v[i].id != NULL)
        {
            free(a->v[i].id);
        }
    }

}


sector* vvod(int *df)
{
    int f = 0, che = 0;
    (*df) = 0;
    
    char *s = readline("Введите данные пассажиров:  ");
    if(s == NULL)
    {
        (*df) = -1;
        free(s);
        return NULL;
    }
    sector *a = (sector*)calloc(1, sizeof(sector));
    a->v = (pass*)calloc(1, sizeof(pass));
    a->k = 0;
    a->n = 0;

    char *token = mstrtok(s, " \t");
    if(token != NULL)
    {
        int k = 0;
        che = sscanf(token, "%d", &k);
        if(che != 1 || k <= 0)
            {
                ochit(a, 0);
                free(s);
                return NULL;
            }
        a->k = k;
    }

    token = mstrtok(NULL, " \t");
    if(token == NULL)
        {
            ochit(a, 0);
            free(s);
            return NULL;
        }
    while(token != NULL)
    {
        f++;
        if(f > 1){a->v = realloc(a->v, f * sizeof(pass));}
        a->v[f-1].id = NULL;
        char *tmp = strdup(token);
        int sls = 0;
        for(int j = 0; j < (strlen(tmp)-1); j++)
        {
            if(tmp[j] == '/')
            {
                if(tmp[j+1] == '/')
                {
                    
                    ochist_ch(a, f);
                    ochit(a, 0);
                    free(tmp);
                    free(s);
                    return NULL;
                }
                sls++;
            }
        }

        if(sls != 2 || tmp[0] == '/' || tmp[strlen(tmp)-1] == '/')
        {
                    ochist_ch(a, f);
                    ochit(a, 0);
                    free(tmp);
                    free(s);
                    return NULL;
        }
        char *tok = strtok(tmp, "/");
        for(int i = 0; i < 3; i++)
        {
            int fl = 0, g = 0;
            switch (i)
            {
            case 0:
                a->v[f-1].id = strdup(tok);
                g++;
                break;
            case 1:
                fl = sscanf(tok, "%d", &a->v[f-1].ta);
                if(fl != 1 || a->v[f-1].ta <= 0)
                {
                    ochist_ch(a, f);
                    ochit(a, 0);
                    free(tmp);
                    return NULL;
                }
                else{g++;}
                break;
            case 2:
                fl = sscanf(tok, "%d", &a->v[f-1].ts);
                if(fl != 1 || a->v[f-1].ts <= 0)
                {
                    ochist_ch(a, f);
                    ochit(a, 0);
                    free(tmp);
                    free(s);
                    return NULL;
                }
                else{g++;}
                break;
            }
            tok = strtok(NULL, "/");
        }
        free(tmp);
        token = mstrtok(NULL, " \t");
    }
    a->n = f;
    free(s);
    return a;
}
