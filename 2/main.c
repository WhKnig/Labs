#include <stdlib.h>
#include "str.h"
#include "in.h"
#include <string.h>
#include "mstring.h"
#include "sort.h"


int main()
{
    int df = 0, finish = 1;
    while(finish == 1)
    {
        df = 0;
        sector *a = vvod(&df);

        while(a == NULL)
        {
            if(df == -1)
            {
                return 0;
            }
            a = vvod(&df);
        }


        sort_pass_by_ta(a);
        print(a);
        int f = process(a);
        while(f != 0)
        {
            if(f == -1)
            {
                return 0;
            }
            f = process(a);
        }
        // f = 0;
        // f = zakonchim(&finish);
        // if(f == -1){return 0;}
    }
}