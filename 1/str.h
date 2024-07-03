#ifndef STR_H
#define STR_H

typedef struct Line
{
    int n;
    int *v;
} Line;

typedef struct Matr
{
    int n;
    Line *l;
} Matr;

void freeM(Matr **m);
int* process(const Matr *m);


#endif