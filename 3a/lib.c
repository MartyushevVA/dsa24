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

int insert(Table *table, unsigned int key, char *info)
{
    if (table->csize == table->msize)
        return 2; // переполнение
    for (int i = 0; i < table->csize; i++)
        if (table->ks[i].key == key)
            return 1; // совпадение ключей
    int i = table->csize - 1;
    while (i >= 0 && table->ks[i].key > key)
    {
        table->ks[i + 1] = table->ks[i];
        i--;
    }
    table->ks[i + 1].key = key;
    table->ks[i + 1].info = (char *)calloc(strlen(info) + 1, sizeof(char));
    strcpy(table->ks[i + 1].info, info);
    table->csize++;
    return 0;
}

int delete(Table *table, unsigned int key)
{
    int i = 0;
    while (i < table->csize && table->ks[i].key != key)
        i++;
    if (i == table->csize)
        return 1;
    free(table->ks[i].info);
    for (int j = i; j < table->csize - 1; j++)
        table->ks[j] = table->ks[j + 1];
    table->csize--;
    return 0;
}

KeySpace *find(Table *table, unsigned int key)
{
    int low = 0;
    int high = table->csize - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (table->ks[mid].key == key)
            return &(table->ks[mid]);
        else if (table->ks[mid].key < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return NULL;
}

void print(Table *table)
{
    for (int i = 0; i < table->csize; i++)
    {
        printf("Key: %u\n", table->ks[i].key);
        printf("Info: %s\n", table->ks[i].info);
        printf("--------------------\n");
    }
}

int pfind(Table *table, Table *indiv, unsigned int start, unsigned int end)
{
    for (int i = 0; i < indiv->csize; i++)
        free(indiv->ks[i].info);
    indiv->msize = table->msize;
    indiv->csize = 0;
    indiv->ks = (KeySpace *)realloc(indiv->ks, indiv->msize * sizeof(KeySpace));
    for (int i = 0; i < table->csize; i++)
    {
        unsigned int currkey = table->ks[i].key;
        if (currkey >= start && currkey <= end)
        {
            indiv->ks[indiv->csize].key = currkey;
            indiv->ks[indiv->csize].info = (char *)calloc(strlen(table->ks[i].info) + 1, sizeof(char));
            strcpy(indiv->ks[indiv->csize].info, table->ks[i].info);
            indiv->csize++;
        }
    }
    return indiv->csize;
}

void deleting(Table *table)
{
    for (int i = 0; i < table->csize; i++)
        free(table->ks[i].info);
    free(table->ks);
    free(table);
}