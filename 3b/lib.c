#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

Table *init(int size)
{
    Table *table = (Table *)malloc(sizeof(Table));
    table->msize = size;
    table->csize = 0;
    table->ks = (KeySpace **)calloc(size, sizeof(KeySpace *));
    return table;
}

int get_hash(unsigned int key)
{
    int hash = (int)key;
    hash = (hash << 15) - hash - 1;
    hash = hash ^ (hash >> 12);
    hash = hash + (hash << 2);
    hash = hash ^ (hash >> 4);
    hash = (hash + (hash << 3)) + (hash << 11);
    hash = hash ^ (hash >> 16);
    return hash;
}

int get_last_release(Table *table, unsigned int key)
{
    int hash = get_hash(key) % table->msize, last = 0;
    if (!table->ks[hash])
        return 0;
    KeySpace *ptr = table->ks[hash];
    while (ptr)
    {
        if (ptr->key == key)
            last = (ptr->release > last) ? ptr->release : last;
        ptr = ptr->next;
    }
    return last;
}

int branch_size(Table *table, int ind)
{
    int size = 0;
    KeySpace *ptr = table->ks[ind];
    while (ptr)
    {
        ptr = ptr->next;
        size++;
    }
    return size;
}

KeySpace *get_n_elem(Table *table, int ind, int n)
{
    KeySpace *ptr = table->ks[ind];
    while (n--)
        ptr = ptr->next;
    return ptr;
}

int is_empty(Table *table)
{
    return table->csize == 0;
}

int is_full(Table *table)
{
    return table->csize == table->msize;
}

int insert(Table *table, unsigned int key, unsigned int info)
{
    int hash = get_hash(key) % table->msize, release = get_last_release(table, key) + 1;
    KeySpace *ptr = table->ks[hash], *item = (KeySpace *)malloc(sizeof(KeySpace));
    item->next = table->ks[hash];
    item->info = info;
    item->key = key;
    item->release = release;
    (table->csize)++;
    table->ks[hash] = item;
    /*if (table->ks[hash])
    {
        while (ptr->next)
            ptr = ptr->next;
        ptr->next = item;
        return 1;
    }
    table->ks[hash] = item;*/
    if (!table->ks[hash]->next)
        return 1;
    return 0;
}

int delete(Table *table, unsigned int key)
{
    int hash = get_hash(key) % table->msize;
    KeySpace *ptr = table->ks[hash], *prev = table->ks[hash];
    while (ptr)
    {
        if (ptr->release == get_last_release(table, key) && ptr->key == key)
        {
            if (table->ks[hash] == ptr)
                table->ks[hash] = ptr->next;
            else
                prev->next = ptr->next;
            free(ptr);
            return 0;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return 1;
}

void copy(Elem *dst, KeySpace *src)
{
    dst->info = src->info;
    dst->key = src->key;
    dst->release = src->release;
}

Elem *find(Table *table, unsigned int key, int release, int *size)
{
    int hash = get_hash(key) % table->msize, max_index = branch_size(table, hash);
    Elem *arr = (Elem *)malloc(sizeof(Elem));
    KeySpace *ptr = table->ks[hash];
    *size = 0;
    for (int i = 0; i < max_index; i++)
    {
        if ((ptr->key == key) && ((!release) || (release == ptr->release)))
        {
            copy(&arr[*size], ptr);
            (*size)++;
            arr = (Elem *)realloc(arr, (*size + 1) * sizeof(Elem));
        }
        ptr = ptr->next;
    }
    return arr;
}

int print(Table *table)
{
    for (int i = 0; i < table->msize; i++)
    {
        if (!table->ks[i])
            continue;
        printf("+++++++ Index: %d +++++++\n", i);
        for (int j = 0; j < branch_size(table, i); j++)
        {
            KeySpace *ptr = get_n_elem(table, i, j);
            printf("Key: %u\n", ptr->key);
            printf("Info: %u\n", ptr->info);
            printf("Release: %i\n", ptr->release);
            printf("----------\n");
        }
    }
    return table->csize;
}

int export(Table *table, FILE *file)
{
    if (is_empty(table))
        return 1;
    KeySpace *ptr;
    unsigned int s[2];
    int max_index;
    for (int i = 0; i < table->msize; i++)
    {
        ptr = table->ks[i];
        max_index = branch_size(table, i);
        for (int j = 0; j < max_index; j++)
        {
            s[0] = ptr->key;
            s[1] = ptr->info;
            fwrite(s, sizeof(unsigned int), 2, file);
            ptr = ptr->next;
        }
    }
    return 0;
}

int refresh(Table *table)
{
    if (is_empty(table))
        return 1;
    KeySpace *ptr, *prev;
    int max_index;
    for (int i = 0; i < table->msize; i++)
    {
        ptr = table->ks[i];
        prev = table->ks[i];
        max_index = branch_size(table, i);
        for (int j = 0; j < max_index; j++)
        {
            if (ptr->release != get_last_release(table, ptr->key))
            {
                if (table->ks[i] == ptr)
                    table->ks[i] = ptr->next;
                else
                    prev->next = ptr->next;
                free(ptr);
                j = 0;
                ptr = table->ks[i];
                prev = table->ks[i];
            }
            else
            {
                prev = ptr;
                ptr = ptr->next;
            }
        }
    }
    return 0;
}

void prepare(Table *table)
{
    for (int i = 0; i < table->msize; i++)
    {
        KeySpace *ptr = table->ks[i], *temp = NULL;
        while (ptr)
        {
            temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
        table->ks[i] = NULL;
    }
    table->csize = 0;
}

void clear(Table *table)
{
    prepare(table);
    free(table->ks);
    free(table);
}

int is_prime(int a)
{
    for (int i = 2; i <= a / 2; i++)
        if (a % i == 0)
            return 0;
    return 1;
}

int calculating(int a)
{
    int b = a + 3;
    while (!is_prime(b))
        b++;
    return b;
}

void set_table(Table *table, int new_msize, KeySpace **arr)
{
    int size = table->csize;
    prepare(table);
    table->msize = new_msize;
    table->ks = (KeySpace **)realloc(table->ks, new_msize * sizeof(KeySpace *));
    prepare(table);
    for (int i = 0; i < size; i++)
        insert(table, arr[i]->key, arr[i]->info);
}

KeySpace **export_to_arr(Table *table)
{
    KeySpace **temp = (KeySpace **)calloc(table->csize, sizeof(KeySpace *)), *ptr = NULL;
    int n = 0;
    for (int i = 0; i < table->msize; i++)
    {
        ptr = table->ks[i];
        for (int j = 0; j < branch_size(table, i); j++)
            temp[n++] = ptr;
    }
    return temp;
}

int smart_resize(Table *table)
{
    /*if (is_full(table))
    {
        set_table(table, calculating(table->msize), export_to_arr(table));
        return 2;
    }*/
    return 0;
}