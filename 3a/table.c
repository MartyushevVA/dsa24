#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "logic.h"

/*Должны быть предусмотрены следующие операции: импорт данных из текстового файла;*/

int L_Insert(Table *table, unsigned int key, char *info)
{
    if (find(table, key) != -1)
        return 1; // совпадение ключей
    if (fullness(table))
        return 2; // переполнение
    int i = t_size(table) - 1;
    while (i >= 0 && get_key(table, i) > key)
    {
        move(table, i + 1, i);
        i--;
    }
    inject(table, key, i + 1, info);
    return 0;
}

int L_Delete(Table *table, unsigned int key)
{
    int i = 0;
    while (i < t_size(table) && get_key(table, i) != key)
        i++;
    if (i == t_size(table))
        return 1;
    free(get_info(table, i));
    for (int j = i; j < t_size(table) - 1; j++)
        move(table, j, j + 1);
    resize(table, -1);
    return 0;
}

KeySpace* L_Find(Table *table, unsigned int key)
{
    for (int i = 0; i < t_size(table); i++)
    {
        if (get_key(table, i) == key)
            return get(table, i);
    }
    return NULL;
}

int L_PTask(Table *table, Table *indiv, unsigned int start, unsigned int end)
{
    for (int i = 0; i < t_size(indiv); i++)
        free(get_info(indiv, i));
    synch(table, indiv);
    for (int i = 0; i < t_size(table); i++)
    {
        unsigned int currkey = get_key(table, i);
        if (currkey >= start && currkey <= end)
        {
            inject(indiv, currkey, indiv->csize, get_info(table, i));
        }
    }
    return t_size(indiv);
}

int L_Print(Table *table)
{
    for (int i = 0; i < t_size(table); i++)
    {
        printf("--------------------\n");
        printf("Key: %u\n", get_key(table, i));
        printf("Info: %s\n", get_info(table, i));
        printf("--------------------\n");
    }
    return table->csize % 2;
}