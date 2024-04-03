#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lib.h"
#include "logic.h"
#include "iter.h"

int is_prime(int a)
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

int get_hash(unsigned int key, int size)
{
    int bytes[4];
    int hash = 0;
    for (int i = 3; i >= 0; i--)
    {
        bytes[i] = key % (int)pow(2, 8);
        void clear(Table *);
        key /= pow(2, 8);
    }
    for (int i = 0; i < 4; i++)
        hash = 37 * hash + bytes[i];
    return abs(hash) % size;
}

/*int quick_resize(Table *table)
{
    if (fullness(table))
    {
        set_size(table, calculating(m_size(table)));
        return 1;
    }
    return 0;
}*/

int get_last_release(Table *table, unsigned int key)
{
    int hash = get_hash(key, m_size(table));
    if (!get_master(table, hash))
        return 0;
    Iterator it = begin(table, hash);
    int last = 0;
    while (stuff(it))
    {
        if (get_key(stuff(it)) == key)
            last = fmax(get_release(stuff(it)), last);
        it = next(it);
    }
    return last;
}

int L_Insert(Table *table, unsigned int key, unsigned int info)
{
    int ntf = 0;
    /*if (quick_resize(table))
        ntf += 2;*/
    int hash = get_hash(key, m_size(table));
    if (get_master(table, hash))
    {
        inject_to_branch(table, new_elem(key, get_last_release(table, key), info), hash);
        ntf += 1;
    }
    else
        inject_to_master(table, new_elem(key, get_last_release(table, key), info), hash);
    return ntf;
}

int L_Delete(Table *table, unsigned int key)
{
    int ntf = 0;
    int hash = get_hash(key, m_size(table));
    int lr = get_last_release(table, key);
    Iterator it = begin(table, hash);
    Iterator prev = begin(table, hash);
    while (stuff(it))
    {
        if (get_release(stuff(it)) == get_last_release(table, key) && get_key(stuff(it)) == key)
        {
            if (get_master(table, hash) == stuff(it))
                delete_root(table, hash);
            else
                delete_elem(stuff(prev), stuff(it));
            return 0;
        }
        prev = it;
        it = next(it);
    }
    return 1;
}

KeySpace *L_Find(Table *table, unsigned int key, int *size)
{
    KeySpace *res = (KeySpace *)calloc(1, sizeof(KeySpace));
    int hash = get_hash(key, m_size(table));
    Iterator it = begin(table, hash);
    for (int i = 0; i < branch_size(table, hash); i++)
    {
        if (get_key(stuff(it)) == key)
        {
            copying(stuff(it), &res[*size]);
            *size++;
            res = (KeySpace *)realloc(res, (*size + 1) * sizeof(KeySpace));
        }
        it = next(it);
    }
    return res;
}

int L_Print(Table *table)
{
    for (int i = 0; i < m_size(table); i++)
    {
        if (!get_master(table, i))
            continue;
        for (int j = 0; j < branch_size(table, i); j++)
        {
            printf("--------------------\n");
            printf("Key: %u\n", get_key(get_n_elem(table, i, j)));
            printf("Info: %u\n", get_info(get_n_elem(table, i, j)));
            printf("Release: %i\n", get_release(get_n_elem(table, i, j)));
            printf("--------------------\n");
        }
        printf("++++++++++++++++++++\n");
    }
    return table->csize;
}

void print(KeySpace *mas, int size)
{
    for (int i=0; i<size; i++)
    {
        printf("--------------------\n");
        printf("Key: %u\n", get_key(&mas[i]));
        printf("Info: %u\n", get_info(&mas[i]));
        printf("Release: %i\n", get_release(&mas[i]));
        printf("--------------------\n");
    }
}