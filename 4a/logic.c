#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "logic.h"

int L_Add(Tree *tree, char *key, unsigned int info)
{
    if (insert(tree, key, &info))
    {
        printf("Value: %u ", info);
        return 1;
    }
    return 0;
}

int L_Delete(Tree *tree, char *key)
{
    return delete (tree, key);
}

int L_Search(Tree *tree, char *key_1, char *key_2)
{
    return search(tree, key_1, key_2);
}

int L_Find(Tree *tree, char *key)
{
    unsigned int *item = find(tree, key);
    if (!item)
        return 0;
    printf("Info: %u\n", *item);
    return 1;
}

int L_SFind(Tree *tree, char *key)
{
    int size = 0;
    SFind *arr = sfind_keys(tree, key, &size);
    if (!size)
        return 0;
    for (int i = 0; i < size; i++)
        printf("Key: %s | Info: %u\n", (arr[i]).key, (arr[i]).info);
    free(arr);
    return 1;
}

void L_Tree_Print(Tree *tree)
{
    printTree(tree->root, 0);
}

int L_Graph(Tree *tree)
{
    return 1;
}

unsigned int stoui(char *str)
{
    unsigned int num = 0;
    int i = 0;
    while (str[i] && '0' <= str[i] && str[i] <= '9')
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

int L_Import(Tree *tree, char *fname)
{
    FILE *file = fopen(fname, "r");
    free(fname);
    if (!file)
        return 1;
    char *s = (char *)calloc(1024, sizeof(char));
    unsigned int info = 0;
    char *key = NULL;
    int parity = 0;
    while (fscanf(file, "%s\n", s) == 1)
    {
        if (!parity)
        {
            key = (char *)calloc(strlen(s) + 1, sizeof(char));
            strcpy(key, s);
        }
        else
        {
            info = stoui(s);
            if (dig(info) != (int)strlen(s))
            {
                free(key);
                continue;
            }
            insert(tree, key, &info);
        }
        parity = (parity + 1) % 2;
    }
    free(s);
    fclose(file);
    if (!tree->root)
        return 2;
    return 0;
}