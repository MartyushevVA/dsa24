#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lib.h"
#include "logic.h"

int L_Insert(Table *table, unsigned int key, unsigned int info)
{
    int ntf = 0/*smart_resize(table)*/;
    ntf += insert(table, key, info, get_last_release(table, key) + 1);
    return ntf;
}

int L_Delete(Table *table, unsigned int key)
{
    return remove(table, key);
}

KeySpace *L_Find(Table *table, unsigned int key, int *size, int release)
{
    KeySpace *res = (KeySpace *)calloc(1, sizeof(KeySpace));
    *size = find(table, key, &res, release);
    return res;
}

void print_arr(KeySpace *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("--------------------\n");
        printf("Key: %u\n", arr[i].key);
        printf("Info: %u\n", arr[i].info);
        printf("Release: %i\n", arr[i].release);
        printf("--------------------\n");
    }
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
