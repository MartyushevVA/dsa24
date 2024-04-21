#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

Tree *init()
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
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

unsigned int *find(Tree *tree, char *key)
{
    Node *temp = find_node(tree->root, key);
    if (!temp)
        return NULL;
    return &(temp->info);
}

Node *findMin(Node *ptr)
{
    if (!ptr)
        return NULL;
    while (ptr->left)
        ptr = ptr->left;
    return ptr;
}

int minimum(int a, int b, int c)
{
    int min = a;
    if (b < min)
    {
        min = b;
    }
    if (c < min)
    {
        min = c;
    }
    return min;
}

int levenshteinDistance(char *s1, char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int matrix[len1 + 1][len2 + 1];
    for (int i = 0; i <= len1; i++)
    {
        matrix[i][0] = i;
    }

    for (int j = 0; j <= len2; j++)
    {
        matrix[0][j] = j;
    }

    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            int cost = (s1[i - 1] != s2[j - 1]);
            int deletion = matrix[i - 1][j] + 1;
            int insertion = matrix[i][j - 1] + 1;
            int substitution = matrix[i - 1][j - 1] + cost;
            matrix[i][j] = minimum(deletion, insertion, substitution);
        }
    }
    return matrix[len1][len2];
}

int str_comp(char *a, char *b)
{
    /*int res = 0, i = 0;
    while (a[i] || b[i])
    {
        if (i < strlen(a) && i < strlen(b))
            res += (abs(a[i] - b[i]));
        else if (i < strlen(a))
            res += (a[i] - 30);
        else if (i < strlen(b))
            res += (b[i] - 30);
        i++;
    }
    return res;*/
    return levenshteinDistance(a, b);
}

SFind *sfind_keys(Tree *tree, char *key)
{
    SFind *arr = (SFind *)calloc(1, sizeof(SFind));
    int etal = INT_MAX, temp = 0, n = 0;
    Node *ptr = findMin(tree->root);
    while (ptr)
    {
        temp = str_comp(key, ptr->key);
        etal = (temp < etal) && temp != 0 ? temp : etal;
        ptr = ptr->next;
    }
    ptr = findMin(tree->root);
    while (ptr)
    {
        temp = str_comp(key, ptr->key);
        if (temp == etal)
        {
            arr[n].key = ptr->key;
            arr[n++].info = ptr->info;
            arr = (SFind *)realloc(arr, (n + 1) * sizeof(SFind));
            // arr[n] = NULL;
        }
        ptr = ptr->next;
    }
    return arr;
}

void threading(Tree *tree)
{
    Node *curr = findMin(tree->root);
    if (curr == tree->root)
        return;
    while (curr != tree->root)
    {
        if (curr == curr->parent->left)
        {
            curr->next = findMin(curr->parent->right);
            if (!curr->next)
                curr->next = curr->parent;
        }
        if (curr == curr->parent->right)
            curr->next = curr->parent;
        curr->next->prev = curr;
        curr = curr->next;
    }
}

unsigned int *insert(Tree *tree, char *key, unsigned int info)
{
    Node *ptr = tree->root, *par = NULL;
    unsigned int *old_info;
    int cmp;
    while (ptr)
    {
        par = ptr;
        cmp = strcmp(key, ptr->key);
        if (cmp == 0)
        {
            *old_info = ptr->info;
            ptr->info = info;
            free(key);
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
        tree->root = ptr;
        return NULL;
    }
    cmp = strcmp(key, par->key);
    if (cmp < 0)
        par->left = ptr;
    else
        par->right = ptr;
    threading(tree);
    return NULL;
}

int delete(Tree *tree, char *key)
{
    Node *y = NULL, *par = NULL, *ptr = NULL, *x = find_node(tree->root, key);
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
        tree->root = ptr;
    else if (par->left == y)
        par->left = ptr;
    else
        par->right = ptr;
    if (y != x)
        x->key = y->key;
    free(y->key);
    free(y);
    threading(tree);
    return 0;
}

int search(Tree *tree, char *start, char *end)
{
    Node *curr = findMin(tree->root);
    for (; curr; curr = curr->next)
        printf("%s ", curr->key);
    if (!tree->root)
        return 0;
    return 1;
}

void clear(Tree *tree)
{
    Node *ptr = findMin(tree->root);
    while (ptr->next)
    {
        free(ptr->key);
        ptr = ptr->next;
        free(ptr->prev);
    }
    free(tree->root->key);
    free(tree->root);
    free(tree);
}

void printTree(Node *root, int space)
{
    if (!root)
        return;
    space += 4;
    printTree(root->right, space);
    printf("\n");
    for (int i = 4; i < space; i++)
        printf(" ");
    printf("%s %u\n", root->key, root->info);
    printTree(root->left, space);
}