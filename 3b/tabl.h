#ifndef TABL_H
#define TABL_H

typedef struct KeySpace {
    int busy;//0-1-2
    char* key;
    unsigned info;
} KeySpace;

typedef struct Table {
    KeySpace *ks;
    int msize;
    int csize;
} Table;

Table* create_map(int size);
int insert(Table *map, char *key, unsigned info);
void posmotrim(const Table *map);
void spesial_vivod(const Table *map);
void freak(Table *map);
Table* nashli(const Table *map, char *key);
int delete_k(Table *map, char *key);
int b_out(Table *map);
Table* b_in(int *f);

#endif