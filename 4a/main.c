#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "dilogs.h"
#include "vvod.h"

int main()
{
    tree *tr = (tree*)malloc(sizeof(tree));
    tr->head = NULL;
    gnode *nodes = NULL;
    int fl = 0, end = 0;
    char *key = NULL;

    while(end != -1)
    {
        fl = menu(&end);
        if(fl == -1){end = -1;break;}

        switch (end)
        {
        case 1:
            fl = dilog_3_in(tr, key);
            if(fl == -1){end = -1;break;}
            break;
        case 2:
            if(tr->head != NULL)
            {
                fl = dilog_4_k(tr, key);
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            
            break;
        case 3:
            if(tr->head != NULL)
            {
                fl = dilog_5(tr, key);
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            break;
        case 4:
            if(tr->head != NULL)
            {
                printBinaryTree(tr);
            }
            else{printf("tree is empty\n");}
            
            break;
        case 5:
            if(tr->head != NULL)
            {
                freeTree(tr);
                tr = (tree*)malloc(sizeof(tree));
                tr->head = NULL;
            }


            fl = f_in(tr);
            if(fl == -1){end = -1;break;}
            break;
        case 6:
            if(tr->head != NULL)
            {
                fl = graf(tr);
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            
            break;
            break;
        case 7:
            if(tr->head != NULL)
            {
                fl = dilog_2(tr, key);
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            break;
        case 12:
            end = -1;
            break;
        case 11:
            if(nodes == NULL || tr->head == NULL){printf("tree or nodes is empty\n");break;}
            fl = testing(tr, nodes, 100);
            if(fl == -1){end = -1;break;}
            break;
        case 9:
            if(tr->head != NULL)
            {
                freeTree(tr);
                tr = (tree*)malloc(sizeof(tree));
                tr->head = NULL;
            }

            fl = dilog_7(tr);
            if(fl == -1){end = -1;break;}
    
            break;
        case 10:
            if(nodes != NULL)
            {
                freenodes(nodes);
            }
            
            nodes = gen_nodes(100);
            break;
        case 8:
            if(tr->head != NULL)
            {
                fl = dilog_6(tr, key);
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            break;
        default:
            break;
        }
    }
    freeTree(tr);
    if(nodes != NULL){freenodes(nodes);}
    return 0;
}