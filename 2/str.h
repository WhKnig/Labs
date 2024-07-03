#ifndef STR_H
#define STR_H

typedef struct pass {
    char *id;
    int ta;
    int ts;
} pass;

#ifdef QUEUE_LIST
typedef struct node {
    pass data;
    struct node* next;
} node;

typedef struct queue {
    int count; 
    node *head; 
    node *tail; 
} queue;
#else
typedef struct queue {
    int count;  
    int head; 
    int tail;
    pass *qu;
    int max;
} queue;
#endif

typedef struct sector {
    int k;      
    queue *o;
    int n;
    pass *v;    
    
} sector;


void print(sector *a);
int process(sector *a);

#endif