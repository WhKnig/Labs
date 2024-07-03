#include <stdlib.h>
#include <stdio.h>
#include "str.h"
#include "in.h"

void help(int f)
{
    switch (f)
    {
    case 0:
        printf("Input number!!!\n");
        break;
    case -1:
        printf("GG\n");
        break;
    case 2:
        printf("Think about it! ;)\n");
        break;
    }
}


int input(int *n, int v)
{
    int flag = scanf("%d", n);
    if (flag == 0)
    {
        help(0);
        return 0;
    }
    else
    {
        if (flag == EOF)
        {
            help(-1);
            return -1;
        }
        else{
            if (v == 1)
            {
                if ((*n) > 0)
                {
                    return 1;
                }
                else
                {
                    help(2);
                    return 2;
                }
            }
            else
            {
                return 1;
            }
        }
    }
}



Matr* vvvod()
{
    int ks = 0, done = 0, ch = 0, p = 0;
    Matr *m = (Matr*)malloc(1 * sizeof(Matr));
  
    printf("Введите количество строк в матрице (для завершения введите EOF): ");
    ch = input(&m->n, 1);
    while(ch != 1){
        if (ch == -1)
        {
            freeM(&m);
            done = 1;
            return NULL;
        }
        scanf("%*[^\n]");
        printf("Введите количество строк в матрице (для завершения введите EOF): ");
        ch = input(&m->n, 1);
    }


    m->l = (Line*)malloc(m->n * sizeof(Line));
    for (int i = 0; i < m->n; i++)
    {
        scanf("%*[^\n]");
        printf("\nВведите количество элементов в строке: ");
        ch = input(&m->l[i].n, 1);
        while(ch != 1){
            if (ch == -1)
            {
                m->n = i;
                freeM(&m);
                done = 1;
                return NULL;
            }
            scanf("%*[^\n]");
            printf("\nВведите количество элементов в строке: ");
            ch = input(&m->l[i].n, 1);
        }

        m->l[i].v = (int*)malloc(m->l[i].n * sizeof(int));

        for (int j = 0; j < m->l[i].n; j++)
        {
            scanf("%*[^\n]");
            printf("Введите элемент матрицы: ");
            ch = input(&m->l[i].v[j], 0);
            while(ch != 1){
                if (ch == -1)
                {
                    m->n = i + 1;
                    freeM(&m);
                    done = 1;
                    return NULL;
                }
                scanf("%*[^\n]");
                printf("Введите элемент матрицы: ");
                ch = input(&m->l[i].v[j], 0);
            }
        }
    }
    return m;
}

