#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "logic.h"

int L_Insert(Table *table, unsigned int key, unsigned int info)
{
    return insert(table, key, info);
}

int L_Delete(Table *table, unsigned int key)
{
    return delete(table, key);
}

int L_Find(Table *table, unsigned int key, int release)
{
    int size;
    Elem *arr = find(table, key, release, &size);
    for (int i = 0; i < size; i++)
    {
        printf("--------------------\n");
        printf("Key: %u\n", arr[i].key);
        printf("Info: %u\n", arr[i].info);
        printf("Release: %i\n", arr[i].release);
        printf("--------------------\n");
    }
    free(arr);
    return size;
}

int L_Print(Table *table)
{
    return print(table);
}

int L_Import(Table *table, char *fname)
{
    FILE *file = fopen(fname, "rb");
    free(fname);
    if (file == NULL)
        return 1;
    unsigned int s[2];
    prepare(table);
    while (fread(s, sizeof(unsigned int), 2, file))
        L_Insert(table, s[0], s[1]);
    fclose(file);
    if (is_empty(table))
        return 2;
    return 0;
}

int L_Export(Table *table, char *fname)
{
    FILE *file = fopen(fname, "wb");
    free(fname);
    export(table, file);
    fclose(file);
    return 0;
}

int L_Refresh(Table *table)
{
    return refresh(table);
}