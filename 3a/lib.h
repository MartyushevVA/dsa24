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

Table *init(int);
void clear(Table *);
void inject(Table *, unsigned int, int, char *);
unsigned int get_key(Table *, int);
char *get_info(Table *, int);
int t_size(Table *);
void move(Table *, int, int);
void resize(Table *, int);
KeySpace *get(Table *, int);
void synch(Table *, Table *);
int fullness(Table *);
int find(Table *, unsigned int);
void preparing(Table *);

#endif