#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "vl.h"


int addque(queue *q, pass p) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = p;
    newNode->next = NULL;
    if (q->head == NULL) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->count++;
    return 0;
}

void dequeue(queue *q) {
    if (q->head != NULL) {
        node *temp = q->head;
        q->head = q->head->next;
        free(temp->data.id);
        free(temp);
        q->count--;
    }
}

void printq(queue *q, int time, int k) {
    printf("\n\n");
    printf("Time\t№\tPass_id\n");
    for (int i = 0; i < k; i++) {
        printf("%d\t%d\t", time, i+1);
        node *current = q[i].head;
        while (current != NULL) {
            printf("%s ", current->data.id);
            current = current->next;
        }
        printf("\n");
    }
}

int check_finish(queue *q, int k) {
    int fl = 0;
    for (int i = 0; i < k; i++) {
        if (q[i].head != NULL) {
            q[i].head->data.ts--;
            if (q[i].head->data.ts == 0) {
                dequeue(&q[i]);
                fl = 1;
            }
        }
    }
    if(fl == 1)
    {return 0;}
    else{return 1;}
}

int create_queue(sector *a)
{
    return 0;
}

void free_sector(sector *a) {
    free(a->o);
    free(a->v);
}

void free_queue(queue *q)
{
    printf("этого никто не ожидал");
}