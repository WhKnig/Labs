#include <stdio.h>
#include <stdlib.h>
#include "tabl.h"
#include "vvod.h"
#include "dilogs.h"
// #include "fin.h"

int main()
{
    int end = 0, fl = 0, ch = 0, chn = 0;
    Table *map = NULL;
    Table *new = NULL;
    char *key = NULL, *info = NULL;

    while(end != -1)
    {
        fl = menu(&end);
        if(fl == -1){end = -1;break;}
        
        switch (end)
        {
            case 1:
                if(ch == 0){printf("Таблица незадана\n");break;}
                fl = dilog_3_in(map, key, info);
                if(fl != 0){end = -1;break;}
                break;
            case 2:
                if(ch != 0)
                {
                    fl = dilog_4_kv(map, key);
                    if(fl != 0){end = -1;break;}
                }
                else{printf("Таблица пуста\n");}
                break;    
            case 3:
                int f = 0;
                if(ch !=0){if(chn != 0){freak(new);
                new = NULL; chn = 0;}}else{printf("Таблица пуста\n");break;}
                f = dilog_2(&new, map, &chn);
                if(f != 0){end = -1;}
                break;
            case 4:
                if(ch != 0){posmotrim(map);}
                else{printf("Таблица пуста\n");}
                break;
            case 5:
                if(ch != 0){freak(map); map = NULL; ch = 0;}
                int kl = 0;
                map = f_in(&kl);
                if(kl != 0){end = -1;break;}
                if(map == NULL){ch = 0;}else{ch = 1;posmotrim(map);}
                break;
            case 6:
               if(ch != 0)
               {
                    fl = dilog_5_k(map, key);
                    if(fl != 0){end = -1;break;}
                }
                else{printf("Таблица пуста\n");}
                break;
            case 7:
                if(ch != 0){reorganize(map);}else{printf("Таблица пуста\n");}
                break;
            case 9:
                end = -1;
                break;
            case 8:
                fl = 0;
                if(ch != 0){freak(map);map = NULL; ch = 0;}
                
                fl = dilog_1(&map, &ch);
                if(fl != 0){end = -1;}
                break;
            case 10:
                if(chn != 0){posmotrim(new);}
                else{printf("Таблица пуста\n");}
                break;
            default:
                break;
        }
    }
    if(ch != 0){freak(map);}
    if(chn != 0){freak(new);}
    if(key != NULL){free(key);}
    if(info != NULL){free(info);}

    return 0;
}