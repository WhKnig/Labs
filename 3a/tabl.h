#ifndef TABL_H
#define TABL_H

typedef struct KeySpace {
    int busy;
    char* key;
    int release;
    char *info;
} KeySpace;

typedef struct Table {
    KeySpace *ks;
    int msize;
    int csize;
} Table;

Table* create_map(int size);
int insert(Table *map, char *key, char *info);
void posmotrim(const Table *map);
void freak(Table *map);
void reorganize(Table *map);
Table* nashli(const Table *map, char *key);
Table* f_in(int *f);
int delete_k(Table *map, char *key);
int delete_kv(Table *map, char *key, int v);


#endif