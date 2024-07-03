#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dilogs.h"
#include "vvod.h"

int main()
{
    Graf *graf = NULL;
    int fl = 0, end = 0, init = 0;
    

    while(end != -1)
    {
        fl = menu(&end);
        if(fl == -1){end = -1;break;}

        switch (end)
        {
        case 1:
            if(init == 1)
            {
                free_graf(graf);
                init = 0;
            }
            graf = calloc(1, sizeof(Graf));
            init = 1;
            break;
        case 2:
            if(init == 0){printf("Граф не задан!\n");break;}
            fl = dialog_dob_ver(graf);
            if(fl == -1){end = -1;}
            break;
        case 3:
            if(init == 0){printf("Граф не задан!\n");break;}
            fl = dialog_dob_rebr(graf);
            if(fl == -1){end = -1;}
            break;
        case 4:
            if(init == 0){printf("Граф не задан!\n");break;}
            fl = dialog_del_rebr(graf);
            if(fl == -1){end = -1;}
            break;
        case 5:
            if(init == 0){printf("Граф не задан!\n");break;}
            fl = dialog_del_ver(graf);
            if(fl == -1){end = -1;}
            break;
        case 6:
            if(init == 0){printf("Граф не задан!\n");break;}
            fl = dialog_ex_ver(graf);
            if(fl == -1){end = -1;}
            break;
        case 7:
            if(init == 0){printf("Граф не задан!\n");break;}
            fl = dialog_ex_rebr(graf);
            if(fl == -1){end = -1;}
            break;
        case 8:
            if(init == 0){printf("Граф не задан!\n");break;}
            print_graf(graf);
            break;
        case 9:
            if(init == 0){printf("Граф не задан!\n");break;}
            grafic(graf);
            break;
        case 10:
            if(init == 0){printf("Граф не задан!\n");break;}
            fl = dialog_obhod(graf);
            if(fl == -1){end = -1;}
            break;
        case 11:
            if(init == 0){printf("Граф не задан!\n");break;}
            fl = dialog_b_f(graf);
            if(fl == -1){end = -1;}
            break;
        case 12:
            if(init == 0){printf("Граф не задан!\n");break;}
            fl = dialog_mst(graf);
            if(fl == -1){end = -1;}
            break;
        case 13:
            end = -1;
            break;
        default:
            break;
        }
    }
    free_graf(graf);
    return 0;
}