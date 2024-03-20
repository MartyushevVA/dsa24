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
int insert(Table *table, unsigned int key, char *info);
int delete(Table *table, unsigned int key);
KeySpace *find(Table *table, unsigned int key);
void print(Table *table);
// int import(Table *table, /*файл*/);
int pfind(Table *table, Table *filler, unsigned int begin, unsigned int end);
void deleting(Table *table);

#endif