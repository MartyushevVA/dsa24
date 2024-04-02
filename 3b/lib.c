#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

Table *init(int size)
{
    Table *table = (Table *)malloc(sizeof(Table));
    table->msize = size;
    table->csize = 0;
    table->ks = (KeySpace *)malloc(size * sizeof(KeySpace));
    zeration(table, 0, size);
    return table;
}

int fullness(Table *table)
{
    return table->csize == table->msize;
}

int c_size(Table *table)
{
    return table->csize;
}

int m_size(Table *table)
{
    return table->msize;
}

void zeration(Table *table, int a, int b)
{
    for (int i = a; i < b; i++)
        table->ks[i] = NULL;
}

void set_size(Table *table, int msize)
{
    int prev = table->msize;
    table->msize = msize;
    table->ks = (KeySpace *)realloc(table->ks, msize * sizeof(KeySpace));
    zeration(table, prev, msize);
}

KeySpace *get_master(Table *table, int hash)
{
    return table->ks[hash];
}

KeySpace *new_elem(unsigned int key, int release, unsigned int info)
{
    KeySpace *elem = (KeySpace *)malloc(sizeof(KeySpace));
    elem->info = info;
    elem->key = key;
    elem->next = NULL;
    elem->release = release;
    return elem;
}

void inject_to_master(Table *table, KeySpace *item, int position)
{
    table->ks[position] = item;
    table->csize++;
}

void inject_to_branch(Table *table, KeySpace *item, int position)
{
    KeySpace *ptr = table->ks[position];
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = item;
    table->csize++;
}

void copying(KeySpace *src, KeySpace *dst)
{
    dst->info = src->info;
    dst->key = src->key;
    dst->next = NULL;
    dst->release = src->release;
}

int branch_size(Table *table, int hash)
{
    int size = 0;
    KeySpace *ptr = table->ks[hash];
    while (ptr)
    {
        ptr = ptr->next;
        size++;
    }
    return size;
}

unsigned int get_key(KeySpace *item)
{
    return item->key;
}

int get_release(KeySpace *item)
{
    return item->release;
}