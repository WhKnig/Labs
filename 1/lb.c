#include <stdlib.h>
#include <stdio.h>
#include "str.h"
#include "in.h"


int main()
{
    int done = 0;

    while (done == 0)
    {
        Matr *m = vvvod();
        if(m == NULL)
        {
            done = 1;
            return 0;
        }
        scanf("%*[^\n]");
        printf("Введенная матрица:\n");
        for (int i = 0; i < m->n; i++)
        {
            for (int j = 0; j < m->l[i].n; j++)
            {
                printf("%-5d  ", m->l[i].v[j]);
            }
            printf("\n\n");
        }

        int *res = process(m);
        scanf("%*[^\n]");
        printf("Результирующий вектор: {  ");
        for (int i = 0; i < m->n; i++)
        {
            printf("%d  ", res[i]);
        }
        scanf("%*[^\n]");
        printf("}\n\n\n\n");
        scanf("%*[^\n]");
        printf("            НОВАЯ МАТРИЦА\n\n");
        freeM(&m);
        free(res);
    }

    return 0;
}
