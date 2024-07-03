#ifndef VL_H
#define VL_H
#include "str.h"

int addque(queue *q, pass p); 
void printq(queue *q, int time, int k);
int check_finish(queue *q, int k);
int create_queue(sector *a);
void free_queue(queue *q);
void free_sector(sector *a);

#endif