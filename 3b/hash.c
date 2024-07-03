#include <stdio.h>
#include "hash.h"

int nod(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long hash(const char *key) 
{
    unsigned long long h = 0;
    while (*key) {
        h += *key++;
        h += h << 10;
        h ^= h >> 6;
    }
    h += h << 3;
    h ^= h >> 11;
    h += h << 15;
    return h;
}

unsigned long long hash2(const char *key)
{
    unsigned long long  h = 0;
    unsigned p_pow = 1;
    
    for(int i = 0; key[i]; i++)
    {
        h += key[i]*p_pow;
        p_pow = p_pow * 61;
    }
    return h;
}

int is_prost(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) 
        {
            return 0;
        }
    }
    return 1;
}

int min_prost(int n) {
    for (int i = n - 1; i >= 2; i--) {
        if (is_prost(i) == 1) 
        {
            return i;
        }
    }
    return 1;
}

void get_data(const char *key, const int m, unsigned *step, unsigned *n)
{
    unsigned long long h = hash(key);
    unsigned long long h2 = hash2(key);

    (*n) = h%m;
    (*step) = 1 + (h2%((m/2)+1));
    while(nod(m, (*step)) != 1)
    {
        (*step) = min_prost((*step));
    }

}