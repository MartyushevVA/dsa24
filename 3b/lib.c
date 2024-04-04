#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

Table *init(int size)
{
    Table *table = (Table *)malloc(sizeof(Table));
    table->msize = size;
    table->csize = 0;
    table->ks = (KeySpace **)calloc(size, sizeof(KeySpace *));
    return table;
}

int get_hash(Table *table, unsigned int key)
{
    /*int bytes[4];
    int hash = 0;
    for (int i = 3; i >= 0; i--)
    {
        bytes[i] = key % (int)pow(2, 8);
        void clear(Table *);
        key /= pow(2, 8);
    }
    for (int i = 0; i < 4; i++)
        hash = 37 * hash + bytes[i];*/
    int hash = ((key >> 16) ^ key) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = (hash >> 16) ^ hash;
    return abs(hash) % table->msize;
}

int max1(int a, int b)
{
    return ((a > b) ? a : b);
    /*if (a > b)
        return a;
    else
        return b;*/
}

int get_last_release(Table *table, unsigned int key)
{
    int hash = get_hash(table, key);
    if (!table->ks[hash])
        return 0;
    int last = 0;
    KeySpace *ptr = table->ks[hash];
    while (ptr)
    {
        if (ptr->key == key)
            last = max1(ptr->release, last);
        ptr = ptr->next;
    }
    return last;
}

int insert(Table *table, unsigned int key, unsigned int info, int release)
{
    int hash = get_hash(table, key);
    KeySpace *ptr = table->ks[hash];
    KeySpace *item = (KeySpace *)malloc(sizeof(KeySpace));
    item->next = NULL;
    item->info = info;
    item->key = key;
    item->release = release;
    (table->csize)++;
    if (table->ks[hash])
    {
        while (ptr->next)
            ptr = ptr->next;
        ptr->next = item;
        return 1;
    }
    table->ks[hash] = item;
    return 0;
}

int remove(Table *table, unsigned int key)
{
    int hash = get_hash(table, key);
    KeySpace *ptr = table->ks[hash];
    KeySpace *prev = table->ks[hash];
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

int find(Table *table, unsigned int key, KeySpace **arr, int release)
{
    int hash = get_hash(table, key);
    KeySpace *ptr = table->ks[hash];
    int size = 0;
    for (int i = 0; i < branch_size(table, hash); i++)
    {
        if (ptr->key == key && ((!release) || (release == ptr->release)))
        {
            (*arr)[size]->info = ptr->info;
            (*arr)[size]->key = ptr->key;
            (*arr)[size]->next = NULL;
            (*arr)[size]->release = ptr->release;
            size++;
            *arr = (KeySpace *)realloc(*arr, (size + 1) * sizeof(KeySpace));
        }
        ptr = ptr->next;
    }
    return size;
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

int print(Table *table)
{
    for (int i = 0; i < table->msize; i++)
    {
        if (table->ks[i])
            continue;
        for (int j = 0; j < branch_size(table, i); j++)
        {
            KeySpace *ptr = get_n_elem(table, i, j);
            printf("--------------------\n");
            printf("Key: %u\n", ptr->key);
            printf("Info: %u\n", ptr->info);
            printf("Release: %i\n", ptr->release);
            printf("--------------------\n");
        }
        printf("++++++++++++++++++++\n");
    }
    return table->csize;
}

KeySpace *get_n_elem(Table *table, int pos, int n)
{
    KeySpace *ptr = table->ks[pos];
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

int export(Table *table, FILE *file)
{
    if (is_empty(table))
        return 1;
    KeySpace *ptr;
    unsigned int s[2];
    for (int i = 0; i < table->msize; i++)
    {
        ptr = table->ks[i];
        for (int j = 0; j < branch_size(table, i); j++)
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
    KeySpace *ptr;
    KeySpace *prev;
    for (int i = 0; i < table->msize; i++)
    {
        ptr = table->ks[i];
        prev = table->ks[i];
        for (int j = 0; j < branch_size(table, i); j++)
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

void clear(Table *table)
{
    for (int i = 0; i < table->msize; i++)
    {
        KeySpace *ptr = table->ks[i];
        KeySpace *temp = NULL;
        while (ptr)
        {
            temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    free(table->ks);
    free(table);
}

/*int is_prime(int a)
{
    for (int i = 2; i <= a / 2; i++)
        if (a % i == 0)
            return 0;
    return 1;
}

int calculating(int a)
{
    int b = a + 1;
    while (!is_prime(b))
        b++;
    return b;
}

int smart_resize(Table *table)
{
    if (is_full(table))
    {
        set_size(table, calculating(table->msize));
        return 2;
        // изменяется хэш-функция, т. е. нужно пересобирать таблицу
        // по-новому, но хз
    }
    return 0;
}

void set_size(Table *table, int msize)
{
    int prev = table->msize;
    table->msize = msize;
    table->ks = (KeySpace **)realloc(table->ks, msize * sizeof(KeySpace *));
    zeration(table, prev, msize);
}*/