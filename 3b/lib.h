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

typedef struct Elem
{
    unsigned int key;
    int release;
    unsigned int info;
} Elem;

Table *init(int);
void clear(Table *);
void prepare(Table *);

int insert(Table *, unsigned int, unsigned int);
int delete(Table *, unsigned int);
Elem *find(Table *, unsigned int, int, int *);
int print(Table *);
int export(Table *, FILE *);
int refresh(Table *);

#endif