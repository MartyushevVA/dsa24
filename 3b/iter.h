#ifndef ITER_H
#define ITER_H
#include "lib.h"

typedef struct Iterator
{
    KeySpace *ptr;
} Iterator;

Iterator begin(Table *table, int hash)
{
    Iterator iterator;
    iterator.ptr = table->ks[hash];
    return iterator;
}

Iterator next(Iterator it)
{
    Iterator iterator;
    iterator.ptr = it.ptr->next;
    return iterator;
}

KeySpace *stuff(Iterator it)
{
    return it.ptr;
}

#endif