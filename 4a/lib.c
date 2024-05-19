#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

Tree *init()
{
    Tree *tree = (Tree *)calloc(1, sizeof(Tree));
    return tree;
}

void clear(Node *node)
{
    if (!node)
        return;
    clear(node->left);
    clear(node->right);
    free(node->key);
    free(node);
}

Node *init_node(char *key, unsigned int info)
{
    Node *elem = (Node *)calloc(1, sizeof(Node));
    elem->key = strdup(key);
    elem->info = info;
    return elem;
}

Node *find_node(Node *node, char *key)
{
    if (!node)
        return NULL;
    if (strcmp(key, node->key) == 0)
        return node;
    if (strcmp(key, node->key) < 0)
        return find_node(node->left, key);
    return find_node(node->right, key);
}

Node *find_min(Node *node)
{
    if (!node)
        return NULL;
    while (node->left)
        node = node->left;
    return node;
}

Node *find_max(Node *node)
{
    if (!node)
        return NULL;
    while (node->right)
        node = node->right;
    return node;
}

Node *find_deepest(Node *node)
{
    if (!node)
        return NULL;
    while (node->left || node->right)
    {
        if (node->left)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

char *beautify_string(char *str)
{
    int i = 0;
    while (str[i++])
        if (str[i] == '/')
            str[i] = '.';
    return str;
}

void threading(Tree *tree)
{
    Node *node = find_deepest(tree->root);
    Node *temp = NULL;
    while (node != tree->root)
    {
        if (node == node->parent->left)
        {
            temp = find_deepest(node->parent->right);
            if (temp)
                node->next = temp;
            else
                node->next = node->parent;
        }
        if (node == node->parent->right)
            node->next = node->parent;
        node->next->prev = node;
        node = node->next;
    }
}

unsigned int *find_info(Tree *tree, char *key)
{
    Node *node = find_node(tree->root, key);
    if (!node)
        return NULL;
    return &(node->info);
}

int power(int x, int a)
{
    while (a--)
        x *= x;
    return x;
}

int my_strcmp(char *str1, char *str2)
{
    int i;
    for (i = 0; str1[i] && str2[i]; i++)
        if (str1[i] - str2[i])
            return abs(str1[i] - str2[i]);
    return abs(str1[i] - str2[i]);
}

int compare_string(char *str1, char *str2)
{
    int count = 0;
    for (int i = 0; str1[i] && str2[i]; i++)
    {
        if (str1[i] == str2[i])
            count += power(25 - i, 2);
        else
            break;
    }
    return abs(my_strcmp(str1, str2)) * (100000 - count);
}

SFind *special_find(Tree *tree, char *key, int *size)
{
    SFind *arr = (SFind *)calloc((*size) + 1, sizeof(SFind));
    int diff = 0, old_diff = INT_MAX;
    Node *node = tree->root;
    while (node)
    {
        diff = compare_string(key, node->key);
        if ((diff < old_diff) * diff)
        {
            *size = 0;
            old_diff = diff;
        }
        if (diff == old_diff)
        {
            arr = (SFind *)realloc(arr, (*size + 1) * sizeof(SFind));
            arr[*size].key = node->key;
            arr[*size].info = node->info;
            (*size)++;
        }
        if (node->left && node->right)
        {
            Node *additional = NULL;
            if (compare_string(node->left->key, key) == compare_string(node->right->key, key))
            {
                arr = (SFind *)realloc(arr, (*size + 2) * sizeof(SFind));
                additional = find_min(node->right);
                arr[*size].key = additional->key;
                arr[*size].info = additional->info;
                additional = find_max(node->left);
                arr[*size + 1].key = additional->key;
                arr[*size + 1].info = additional->info;
                (*size) += 2;
                break;
            }
            if (compare_string(node->left->key, key) < compare_string(node->right->key, key))
            {
                additional = find_min(node->right);
                if (compare_string(key, additional->key) <= diff)
                {
                    arr = (SFind *)realloc(arr, (*size + 1) * sizeof(SFind));
                    arr[*size].key = additional->key;
                    arr[*size].info = additional->info;
                    (*size)++;
                }
                node = node->left;
            }
            else
            {
                additional = find_max(node->left);
                if (compare_string(key, additional->key) <= diff)
                {
                    arr = (SFind *)realloc(arr, (*size + 1) * sizeof(SFind));
                    arr[*size].key = additional->key;
                    arr[*size].info = additional->info;
                    (*size)++;
                }
                node = node->right;
            }
        }
        else
        {
            node = node->right ? node->right : (node->left ? node->left : NULL);
            if (!node)
                break;
        }
    }
    return arr;
}

int insert(Tree *tree, char *key, unsigned int *info)
{
    Node *node = tree->root, *par = NULL;
    unsigned int old_info = 0;
    int cmp;
    while (node)
    {
        par = node;
        cmp = strcmp(key, node->key);
        if (cmp == 0)
        {
            old_info = node->info;
            node->info = *info;
            *info = old_info;
            return 1;
        }
        if (cmp < 0)
            node = node->left;
        else
            node = node->right;
    }
    node = init_node(key, *info);
    node->parent = par;
    if (!par)
    {
        tree->root = node;
        return 0;
    }
    cmp = strcmp(key, par->key);
    if (cmp < 0)
        par->left = node;
    else
        par->right = node;
    return 0;
}

int delete(Tree *tree, char *key)
{
    Node *x = find_node(tree->root, key), *y = NULL;
    Node *node = NULL, *par = NULL;
    if (!x)
        return 1;
    if (!x->left || !x->right)
        y = x;
    else
        y = find_min(x->right);
    if (y->left)
        node = y->left;
    else
        node = y->right;
    par = y->parent;
    if (node)
        node->parent = par;
    if (!par)
        tree->root = node;
    else if (par->left == y)
        par->left = node;
    else
        par->right = node;
    if (y != x)
    {
        free(x->key);
        x->key = y->key;
        x->info = y->info;
        free(y);
    }
    else
    {
        free(y->key);
        free(y);
    }
    return 0;
}

int search(Tree *tree, char *begin, char *end)
{
    if (!tree->root)
        return 0;
    threading(tree);
    Node *node = find_deepest(tree->root);
    while (node)
    {
        if (strcmp(begin, node->key) <= 0 && strcmp(end, node->key) >= 0)
            printf("%s ", node->key);
        node = node->next;
    }
    printf("\n");
    return 1;
}

void format_print(Node *node, int space)
{
    if (!node)
        return;
    space += 4;
    format_print(node->right, space);
    printf("\n");
    for (int i = 4; i < space; i++)
        printf(" ");
    printf("%s %u\n", node->key, node->info);
    format_print(node->left, space);
}

void graphviz(Node *node, FILE *fp, int *filler)
{
    if (!node)
        return;
    (*filler)++;
    fprintf(fp, "    %s;\n", beautify_string(node->key));
    if (node->left)
    {
        fprintf(fp, "    %s -> %s;\n", beautify_string(node->key), beautify_string(node->left->key));
        if (!node->right)
            fprintf(fp, "    %d [style=invis];\n    %s -> %d [style=invis];\n", *filler, beautify_string(node->key), *filler);
        graphviz(node->left, fp, filler);
    }
    if (node->right)
    {
        if (!node->left)
            fprintf(fp, "    %d [style=invis];\n    %s -> %d [style=invis];\n", *filler, beautify_string(node->key), *filler);
        fprintf(fp, "    %s -> %s;\n", beautify_string(node->key), beautify_string(node->right->key));
        graphviz(node->right, fp, filler);
    }
}