#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "vl.h"
#include "in.h"

void print(sector *a) {
    for (int i = 0; i < a->n; i++) {
        printf("%s/%d/%d\t", a->v[i].id, a->v[i].ta, a->v[i].ts);
    }
    printf("\n");
}

int empty_queue(queue *q, int k) {
    for(int i = 0; i < k; i++) {
        if(q[i].count != 0) {
            return 0;
        }
    }
    return 1;
}



int process(sector *a) {
    int fl = 0;
    a->o = (queue*)calloc(a->k, sizeof(queue));

    fl = create_queue(a);
    if(fl == -1){
        free_sector(a);
        free(a);
        return -1;
    }

    int time = 1, check = 0, n = 0, ind = 0, stop = 0, kon = 0;

    while(stop == 0)
    {
        while(a->v[ind].ta == time)
        {
            check = ind % a->k;
            n = addque(a->o+check, a->v[ind]);
            if(n == 1) {
                for (int i = 0; i < a->k; i++) {
                free_queue(a->o+i);
                }
                free(a->o);
                
                return 1; 
            }
            ind++;
            if(ind >= a->n)
            {
                stop = 1;
                break;
            }
        }
        printq(a->o, time, a->k);
        time++;
        kon = check_finish(a->o, a->k);
        if(kon == 0){printq(a->o, time, a->k);}

    }
    
    int sh = 0, shp = 0;
    while(empty_queue(a->o, a->k) == 0) {
        sh = 0;
        shp = 0;
        time++;
        for(int i = 0; i < a->k; i++) {
            sh = sh + a->o[i].count;
        }
        check_finish(a->o, a->k);
        for(int i = 0; i < a->k; i++) {
            shp = shp + a->o[i].count;
        }
        if(shp < sh) {
            printq(a->o, time, a->k);
        }
    }
    free_sector(a);
    free(a);
    return 0;
}
