#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "sort.h"

int compare_pass_by_ta(const void *a, const void* b)
{
    const pass* pass_a = (const pass*)a;
    const pass* pass_b = (const pass*)b;
    return (pass_a->ta) - (pass_b->ta);
}

void sort_pass_by_ta(sector *a)
{
    qsort(a->v, a->n, sizeof(pass), compare_pass_by_ta);
}

