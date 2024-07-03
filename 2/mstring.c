#include <stdio.h>
#include <stdlib.h>
#include "mstring.h"
#include <string.h>

char* mstrtok(char *str, const char *r)
{
    static char *st = NULL;
    char *token = NULL;
    int t = 0, f = 0, lr = 0;
    if (str != NULL)
    {
        st = str;
    }
    t = 0;
    lr =  strlen(r);
    while (*st)
    {  
        f = 0;
        for (int l = 0; l < lr; l++)
        {
            if (*st != r[l])
            {
                f++;
            }
        }
        if(f == lr)
        {
            if(t == 0)
            {
                t++;
                token = st;    
            }
        }
        else if (t == 1)
        {
            *st = '\0';
            ++st;
            break;
        }
        ++st;
    }
    if (t == 0)
    {
        st = NULL;
        return NULL;
    }
    else
    {
        return token;
    }
}
