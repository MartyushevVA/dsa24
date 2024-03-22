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

KeySpace *L_Find(Table *table, unsigned int key)
{
    for (int i = 0; i < t_size(table); i++)
        if (get_key(table, i) == key)
            return get(table, i);
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
            inject(indiv, currkey, indiv->csize, get_info(table, i));
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
    return table->csize;
}

unsigned int stoui(char *str)
{
    unsigned int num = 0;
    int i = 0;
    while (str[i] != '\0' && '0' <= str[i] <= '9')
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return num;
}

int L_Import(Table *table, char *fname)
{
    FILE *file = fopen(fname, "r");
    free(fname);
    char *s = (char *)malloc(1024 * sizeof(char));
    char *info;
    unsigned int key;
    while (fscanf(file, "%s", s) == 1 && !fullness(table))
    {
        char *token = strtok(s, "^");
        if (token != NULL)
        {
            key = stoui(token);
            token = strtok(NULL, "^");
            if (token != NULL)
                inject(table, key, t_size(table), token);
        }
    }
    free(s);
    fclose(file);
    return 0;
}

char *spacetounder(char *str)
{
    int i = 0;
    while (str[i++])
        if (str[i] == ' ')
            str[i] += ('_' - ' ');
    return str;
}

int L_Export(Table *table, char *fname)
{
    FILE *file = fopen(fname, "w");
    free(fname);
    if (!t_size(table))
        return 1;
    for (int i = 0; i < t_size(table); i++)
        fprintf(file, "%u^%s ", get_key(table, i), spacetounder(get_info(table, i)));
    fclose(file);
    return 0;
}