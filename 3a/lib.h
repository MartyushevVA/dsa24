#ifndef LIB_H
#define LIB_H

typedef struct KeySpace
{
    unsigned int key;
    char *info;
} KeySpace;

typedef struct Table
{
    KeySpace *ks;
    int msize;
    int csize;
} Table;

Table *init(int size);
void clear(Table *table);
void inject(Table *table, unsigned int key, int pos, char *info);
unsigned int get_key(Table *table, int pos);
char *get_info(Table *table, int pos);
int t_size(Table *table);
void move(Table *table, int des, int src);
void resize(Table *table, int value);
KeySpace *get(Table *table, int pos);
void synch(Table *table, Table *indiv);
/*
int delete(Table *table, unsigned int key);
KeySpace *find(Table *table, unsigned int key);
int get(Table *table, int index);
 int import(Table *table, файл);
int pfind(Table *table, Table *indiv, unsigned int begin, unsigned int end);*/
int fullness(Table *table);
int find(Table *table, unsigned int key);

#endif