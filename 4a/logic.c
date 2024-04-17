#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "logic.h"

int L_Add(Tree *tree, char *key, unsigned int info)
{
    unsigned int old_info = insert(tree, key, info);
    if (old_info)
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
    Elem *item = find(tree, key);
    if (!item)
        return 0;
    printf("Key: %s | Info: %u", item->key, item->info);
    free(item);
    return 1;
}