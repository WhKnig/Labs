#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "vl.h"


int addque(queue *q, pass p) {
    if (q->count >= q->max) {
        return 1;
    }
    int tail_index = (q->head + q->count) % q->max;
    q->qu[tail_index] = p;
    q->count++;
    return 0;
}

void dequeue(queue *q) {
    if (q->count != 0) {
        q->head = (q->head + 1) % q->max; 
        q->count--;
    }
}

void printq(queue *q, int time, int k) {
    printf("\n\n");
    printf("Time\t№\tPass_id\n");
    for (int i = 0; i < k; i++) {
        printf("%d\t%d\t", time, i+1);
        int current_index = q[i].head;
        for (int j = 0; j < q[i].count; j++) {
            if (q[i].qu[current_index].ts != 0) {
                printf("%s ", q[i].qu[current_index].id);
            }
            current_index = (current_index + 1) % q[i].max;
        }
        printf("\n");
    }
}

int check_finish(queue *q, int k){
    int fl = 0;
    for (int i = 0; i < k; i++) {
        if (q[i].count != 0){
            q[i].qu[q[i].head].ts--;
            if (q[i].qu[q[i].head].ts == 0) {
                // printf("zashli");
                dequeue(q+i);
                fl = 1;
            }
        }
    }
    if(fl == 1)
    {return 0;}
    else{return 1;}
}

int create_queue(sector *a) {
    int m = 0, f = 0;
    printf("Введите размер очереди:  ");
    f = scanf("%d", &m);
    while(f != 1 || m <= 0)
    {
        
        scanf("%*[^\n]");
        if(f == -1)
        {
            return -1;
        }
        printf("Ошибка ввода!\n");
        printf("Введите размер очереди:  ");
        f = scanf("%d", &m);

    }
    for (int i = 0; i < a->k; i++) {
        a->o[i].max = m;
        a->o[i].qu = (pass*)calloc(m, sizeof(pass));
        a->o[i].head = 0;
        a->o[i].tail = 0;
    } 
    return 0;  
}

void free_queue(queue *q) {
    free(q->qu);
}

void free_sector(sector *a) {
    for (int i = 0; i < a->k; i++) {
      free_queue(a->o+i);
    }
    free(a->o);
    for(int j = 0; j < a->n; j++)
    {
        free(a->v[j].id);
    }
    free(a->v);
}