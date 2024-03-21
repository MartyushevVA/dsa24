#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

/*Должны быть предусмотрены следующие операции: импорт данных из текстового файла;*/

Table *init(int size)
{
    Table *table = (Table *)malloc(sizeof(Table));
    table->msize = size;
    table->csize = 0;
    table->ks = (KeySpace *)malloc(size * sizeof(KeySpace));
    return table;
}

void clear(Table *table)
{
    for (int i = 0; i < table->csize; i++)
        free(table->ks[i].info);
    free(table->ks);
    free(table);
}

int fullness(Table *table)
{
    return table->csize == table->msize;
}

int find(Table *table, unsigned int key)
{
    for (int i = 0; i < table->csize; i++)
        if (table->ks[i].key == key)
            return i;
    return -1;
}

void inject(Table *table, unsigned int key, int pos, char *info)
{
    table->ks[pos].key = key;
    table->ks[pos].info = (char *)calloc(strlen(info) + 1, sizeof(char));
    strcpy(table->ks[pos].info, info);
    table->csize++;
}

unsigned int get_key(Table *table, int pos)
{
    return table->ks[pos].key;
}

char *get_info(Table *table, int pos)
{
    return table->ks[pos].info;
}

int t_size(Table *table)
{
    return table->csize;
}

void move(Table *table, int des, int src)
{
    table->ks[des] = table->ks[src];
}

void resize(Table *table, int value)
{
    table->csize += (value);
}

KeySpace *get(Table *table, int pos)
{
    return &(table->ks[pos]);
}

void synch(Table *table, Table *indiv)
{
    indiv->msize = table->msize;
    indiv->csize = 0;
    indiv->ks = (KeySpace *)realloc(indiv->ks, indiv->msize * sizeof(KeySpace));
}