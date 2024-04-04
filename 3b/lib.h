#ifndef LIB_H
#define LIB_H

typedef struct KeySpace
{
    unsigned int key;
    int release;
    unsigned int info;
    struct KeySpace *next;
} KeySpace;

typedef struct Table
{
    KeySpace **ks;
    int msize;
    int csize;
} Table;

Table *init(int);
void clear(Table *);

int insert(Table *, unsigned int, unsigned int, int);
int remove(Table *, unsigned int);
int find(Table *, unsigned int, KeySpace **, int);
int print(Table *);
int export(Table *, FILE *);
int refresh(Table *);

//int smart_resize(Table *);
int get_last_release(Table *, unsigned int);
int is_empty(Table *);

#endif