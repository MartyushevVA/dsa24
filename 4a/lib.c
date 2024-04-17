#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

Tree *init()
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    return tree;
}

Node *init_node(char *key, unsigned int info)
{
    Node *elem = (Node *)malloc(sizeof(Node));
    elem->key = strdup(key);
    elem->left = NULL;
    elem->right = NULL;
    elem->next = NULL;
    elem->prev = NULL;
    elem->parent = NULL;
    elem->info = info;
    return elem;
}

Node *find_node(Node *ptr, char *key)
{
    int cmp;
    while (ptr)
    {
        cmp = strcmp(key, ptr->key);
        if (cmp == 0)
            return ptr;
        ptr = cmp < 0 ? ptr->left : ptr->right;
    }
    return NULL;
}

Elem *find(Tree *tree, char *key)
{
    Node *temp = find_node(tree->root, key);
    if (!temp)
        return NULL;
    Elem *item = (Elem *)calloc(1, sizeof(Elem));
    item->key = temp->key;
    item->info = temp->info;
    return item;
}

Node *findMin(Node *ptr)
{
    if (!ptr)
        return NULL;
    while (ptr->left)
        ptr = ptr->left;
    return ptr;
}

unsigned int insert(Node **proot, char *key, unsigned int info)
{
    Node *ptr = *proot, *par = NULL;
    int cmp;
    while (ptr)
    {
        par = ptr;
        cmp = strcmp(key, ptr->key);
        if (cmp == 0)
        {
            unsigned int old_info = ptr->info;
            ptr->info = info;
            return old_info;
        }
        if (cmp < 0)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    ptr = init_node(key, info);
    ptr->parent = par;
    if (par == NULL)
    {
        *proot = ptr;
        return;
    }
    cmp = strcmp(key, par->key);
    if (cmp < 0)
        par->left = ptr;
    else par->right = ptr;
    return;
}

int delete(Node **proot, char *key)
{
    Node *y = NULL, *par = NULL, *ptr = NULL, *x = find_node(*proot, key);
    if (!x)
        return 1;
    if (!(x->left) || !(x->right))
        y = x;
    else
        y = findMin(x->right);
    if (y->left)
        ptr = y->left;
    else
        ptr = y->right;
    par = y->parent;
    if (ptr)
        ptr->parent = par;
    if (!par)
        *proot = ptr;
    else if (par->left == y)
        par->left = ptr;
    else
        par->right = ptr;
    if (y != x)
        x->key = y->key;
    free(y->key);
    free(y);
    return 0;
}

void look_through(Node *root, char *start, char *end, int *flag)
{
    if (root == NULL)
        return;
    int cond = strcmp(root->key, start) > 0 && strcmp(root->key, end) < 0;
    if (cond)
        *flag = 1;
    look_through(root->right, start, end, flag);
    if (cond)
        printf("%s ", root->key);
    look_through(root->left, start, end, flag);
}

int search(Tree *tree, char *start, char *end)
{
    int flag = 0;
    look_through(tree->root, start, end, &flag);
    return flag;
}
