#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "logic.h"

int is_prime(int a)
{
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0)
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
        bytes[i] = key % pow(2, 8);
        key /= pow(2, 8);
    }
    for (int i = 0; i < 4; i++)
        hash = 37 * hash + bytes[i];
    return abs(hash) % size;
}

int quick_resize(Table *table)
{
    if (fullness(table))
    {
        set_size(table, calculating(m_size(table)));
        return 1;
    }
    return 0;
}

int get_last_release(Table *table, unsigned int key)
{
    int hash = get_hash(key, m_size(table));
    if (!get_master(table, hash))
        return 0;
    Iterator it = begin(table, hash);
    int last = 0;
    while (it)
    {
        if (it_key(it) == key)
            last = it_release(it);
        it = next(it);
    }
    return last;
}

int L_Insert(Table *table, unsigned int key, unsigned int info)
{
    int ntf = 0;
    if (quick_resize(table))
        ntf += 2;
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
    if (!branch_size(table, hash))
        return 1;
    Iterator it = begin(table, hash);
    Iterator prev = begin(table, hash);
    while(get_last_release(table, key))
}

KeySpace *L_Find(Table *table, unsigned int key)
{
    KeySpace *res = (KeySpace *)malloc(sizeof(KeySpace));
    int size = 0;
    int hash = get_hash(key, m_size(table));
    if (get_master(table, hash))
    {
        for (Iterator it = begin(table, hash); it_next(it); next(it))
        {
            if (it_key(it) == key)
            {
                copying(it.ptr, res[size]);
                size++;
                res = (KeySpace *)realloc(res, (size + 1) * sizeof(KeySpace));
            }
        }
        return res;
    }
    free(res);
    return NULL;
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
    while (str[i] != '\0' && '0' <= str[i] && str[i] <= '9')
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return num;
}

int dig(unsigned int num)
{
    if (!num)
        return 1;
    int i = 1;
    while (num /= 10)
        i++;
    return i;
}

int L_Import(Table *table, char *fname)
{
    FILE *file = fopen(fname, "r");
    free(fname);
    if (file == NULL)
        return 1;
    char *s = (char *)malloc(1024 * sizeof(char));
    unsigned int key = 0;
    int isfull = 0;
    while (fscanf(file, "%s", s) == 1)
    {
        if (fullness(table))
        {
            isfull = 1;
            break;
        }
        char *token = strtok(s, "^");
        if (token != NULL)
        {
            key = stoui(token);
            if (dig(key) != (int)strlen(token))
                continue;
            token = strtok(NULL, "^");
            if (token != NULL)
                if (find(table, key) == -1)
                    inject(table, key, t_size(table), token);
        }
    }
    free(s);
    fclose(file);
    if (isfull)
        return 3;
    if (!t_size(table))
        return 2;
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