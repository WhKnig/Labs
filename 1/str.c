#include <stdlib.h>
#include <stdio.h>
#include "str.h"

void freeM(Matr **m)
{
    for(int i = 0; i < (*m)->n; i++)
    {
        free((*m)->l[i].v);
    }
    free((*m)->l);
    free((*m));
}

int* process(const Matr* m)
{
    int *r = (int*)malloc(m->n * sizeof(int));
    int c = 0, n = 0;
    for (int i = 0; i < m->n; i++)
    {
        c = 0;
        n = 0;
        for (int j = 0; j < m->l[i].n; j++)
        {
            if (m->l[i].v[j]%2 == 0)
            {
                c = c + m->l[i].v[j];
            }
            else
            {
                n = n + m->l[i].v[j];
            }
        }
        r[i] = c - n;
    }
    return r;
}