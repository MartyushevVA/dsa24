#ifndef LIB_H
#define LIB_H

typedef struct KeySpace
{
    unsigned int key;
    int release;
    unsigned int *info;
    KeySpace *next;
} KeySpace;

typedef struct Table
{
    KeySpace *ks;
    int msize;
    int csize;
} Table;

Table *init(int);
int c_size(Table *);
int m_size(Table *);
int fullness(Table *);
void set_size(Table *, int);
KeySpace *get_master(Table *, int);
KeySpace *new_elem(unsigned int, int, unsigned int);
void inject_to_master(Table *, KeySpace *, int);
void inject_to_branch(Table *, KeySpace *, int);
void copying(KeySpace *, KeySpace *);
int branch_size(Table *, int);
unsigned int get_key(KeySpace *);
int get_release(KeySpace *);

#endif