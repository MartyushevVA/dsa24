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

Node *init_node(unsigned int key, unsigned int info)
{
    Node *elem = (Node *)calloc(1, sizeof(Node));
    elem->key = key;
    elem->info = info;
    return elem;
}

/*-------------------------------*/

Node *find_cert_node(Node *node, unsigned int key, int pos)
{
    if (!node)
        return NULL;
    if (node->key == key)
    {
        Node *ptr = node;
        while (ptr->kmates && pos--)
            ptr = ptr->kmates;
        return ptr;
    }
    if (key < node->key)
        return find_cert_node(node->left, key, pos);
    return find_cert_node(node->right, key, pos);
}

/*-------------------------------*/

Node *find_branch(Node *node, unsigned int key)
{
    if (!node)
        return NULL;
    if (node->key == key)
        return node;
    if (key < node->key)
        return find_branch(node->left, key);
    return find_branch(node->right, key);
}

int print_array(Array *arr)
{
    if (!arr->size)
    {
        free(arr->ks);
        free(arr);
        return 1;
    }
    printf("Key: %u | Infos: ", arr->ks[0]->key);
    for (int i = 0; i < arr->size; i++)
        printf("%u ", arr->ks[i]->info);
    free(arr->ks);
    free(arr);
    return 0;
}

Array *finding(Tree *tree, unsigned int key)
{
    Array *arr = (Array *)calloc(1, sizeof(Array));
    arr->ks = (Node **)calloc(1, sizeof(Node *));
    Node *branch = find_branch(tree->root, key);
    Node *ptr = branch;
    while (ptr)
    {
        arr->ks[arr->size] = ptr;
        (arr->size)++;
        arr->ks = (Node **)realloc(arr->ks, (arr->size + 1) * sizeof(Node *));
        ptr = ptr->kmates;
    }
    return arr;
}

/*-------------------------------*/

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

SFind *special_find(Tree *tree, char *key, int *size)
{
    /*SFind *arr = (SFind *)calloc((*size) + 1, sizeof(SFind));
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
    return arr;*/
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

int search(Tree *tree, unsigned int begin, unsigned int end)
{
    if (!tree->root)
        return 0;
    Node *node = find_deepest(tree->root);
    Node *temp = NULL;
    while (node != tree->root)
    {
        if (node->key <= end && node->key >= begin)
            printf("%s ", node->key);

        if (node == node->parent->left)
        {
            temp = find_deepest(node->parent->right);
            if (temp)
                node = temp;
            else
                node = node->parent;
        }
        else
            node = node->parent;
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
    printf("%s %u\n", node->key);
    format_print(node->left, space);
}

void graphviz(Node *node, FILE *fp, int *filler)
{
    if (!node)
        return;
    (*filler)++;
    fprintf(fp, "    %s;\n", node->key);
    if (node->left)
    {
        fprintf(fp, "    %s -> %s;\n", node->key, node->left->key);
        if (!node->right)
            fprintf(fp, "    %d [style=invis];\n    %s -> %d [style=invis];\n", *filler, node->key, *filler);
        graphviz(node->left, fp, filler);
    }
    if (node->right)
    {
        if (!node->left)
            fprintf(fp, "    %d [style=invis];\n    %s -> %d [style=invis];\n", *filler, node->key, *filler);
        fprintf(fp, "    %s -> %s;\n", node->key, node->right->key);
        graphviz(node->right, fp, filler);
    }
}