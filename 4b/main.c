#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "dilogs.h"
#include "vvod.h"
#include "func.h"

int main()
{
    tree *tr = create_tree();
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
            fl = dilog_insert(tr, key);
          
            if(fl == -1){end = -1;break;}
            break;
        case 2:
            if(!tree_is_empty(tr))
            {
                fl = dilog_delete(tr, key);
               
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            
            break;
        case 3:
            if(!tree_is_empty(tr))
            {
                fl = dilog_search(tr, key);
         
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            break;
        case 4:
            if(!tree_is_empty(tr))
            {
                print_tree(tr);
            }
            else{printf("tree is empty\n");}
            break;
        case 5:
            if(!tree_is_empty(tr))
            {
                delete_tree(tr->root);
                free(tr);
                tr = create_tree();
            }


            fl = f_in(tr);
            if(fl == -1){end = -1;break;}
            break;
        case 6:
            if(!tree_is_empty(tr))
            {
                fl = graf(tr);
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            
            break;
            break;
        case 7:
            if(!tree_is_empty(tr))
            {
                fl = dilog_detour(tr);
            
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            break;
        case 12:
            end = -1;
            break;
        case 11:
            if(nodes == NULL || tree_is_empty(tr)){printf("tree or nodes is empty\n");break;}
            fl = testing(tr, nodes, 100);
            if(fl == -1){end = -1;break;}
            break;
        case 9:
            if(!tree_is_empty(tr))
            {
                delete_tree(tr->root);
                free(tr);
                tr = create_tree();
            }

            fl = dilog_test(tr);
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
            if(!tree_is_empty(tr))
            {
                fl = dilog_sp_search(tr, key);
                if(fl == -1){end = -1;break;}
            }
            else{printf("tree is empty\n");}
            break;
        default:
            break;
        }
    }
    delete_tree(tr->root);
    if(nodes != NULL){freenodes(nodes);}
    free(tr);
    return 0;
}