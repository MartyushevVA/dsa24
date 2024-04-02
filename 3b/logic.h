#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

typedef struct Iterator
{
    KeySpace *ptr;
} Iterator;

Iterator begin(Table* table, int hash)
{
    return Iterator{.ptr = table->ks[hash]};
}

int it_data(Iterator it)
{
    return *it.ptr->info;
}

int it_release(Iterator it)
{
    return *it.ptr->release;
}

int it_key(Iterator it)
{
    return *it.ptr->key;
}

int it_next(Iterator it)
{
    return *it.ptr->next;
}

Iterator next(Iterator it)
{
    return Iterator{.ptr = *it.ptr->next};
}

int L_Insert(Table *, unsigned int, char *);
int L_Delete(Table *, unsigned int);
KeySpace *L_Find(Table *, unsigned int);
int L_Print(Table *);
int L_Import(Table *, char *);
int L_Export(Table *, char *);

#endif