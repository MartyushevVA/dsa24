#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

/*---Инициализация и очистка----------------------------*/

Node *init_node(unsigned int key, unsigned int info, Node *parent)
{
    Node *elem = (Node *)calloc(1, sizeof(Node));
    elem->key = key;
    elem->info = info;
    elem->parent = parent;
    return elem;
}

void remove_node(Node *node)
{
    if (!node)
        return;
    remove_node(node->left);
    remove_node(node->right);
    free(node);
}

Tree *init_tree()
{
    Tree *tree = (Tree *)calloc(1, sizeof(Tree));
    tree->alpha = 0.75;
    return tree;
}

void remove_tree(Tree *tree)
{
    remove_node(tree->root);
    free(tree);
}

Array *set(int size)
{
    srand(time(NULL));
    Array *arr = (Array *)malloc(sizeof(Array));
    arr->size = size;
    arr->ks = (Node **)calloc(size, sizeof(Node *));
    for (int i = 0; i < size; i++)
    {
        arr->ks[i] = (Node *)calloc(1, sizeof(Node));
        arr->ks[i]->info = rand() % 1000000;
        arr->ks[i]->key = rand() % 1000000;
    }
    return arr;
}

void remove_array(Array *arr)
{
    for (int i = 0; i < arr->size; i++)
        free(arr);
}

/*---Поиски нод----------------------------*/

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

/*---Поиск----------------------------*/

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

Array *find_node(Tree *tree, unsigned int key)
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

/*---Калибровка----------------------------*/

int get_size(Node *node)
{
    if (!node)
        return 0;
    return get_size(node->left) + get_size(node->right) + 1;
}

Node *get_sibling(Node *node)
{
    if (!node->parent)
        return NULL;
    return node == node->parent->left ? node->parent->right : node->parent->left;
}

Node *find_scapegoat(Tree *tree, Node *node)
{
    int size = 1, totalSize;
    while (node->parent)
    {
        totalSize = 1 + size + get_size(get_sibling(node));
        if (get_size(node) > tree->alpha * totalSize)
            return node->parent;
        node = node->parent;
        size = totalSize;
    }
    return NULL;
}

int storeNodes(Node *node, Node **nodes, int index)
{
    if (!node)
        return index;
    index = storeNodes(node->left, nodes, index);
    nodes[index] = node;
    index = storeNodes(node->right, nodes, index + 1);
    return index;
}

Node *buildTree(Node **nodes, Node *parent, int start, int end)
{
    if (start > end)
        return NULL;
    int mid = (start + end) / 2;
    Node *node = nodes[mid];
    node->left = buildTree(nodes, node, start, mid - 1);
    node->right = buildTree(nodes, node, mid + 1, end);
    node->parent = parent;
    return node;
}

Node *rebuild(Node *scapegoat)
{
    Node **arr = (Node **)malloc(get_size(scapegoat) * sizeof(Node *));
    int count = storeNodes(scapegoat, arr, 0);
    Node *node = buildTree(arr, NULL, 0, count - 1);
    free(arr);
    return node;
}

/*---Вставка----------------------------*/

int insert_node(Tree *tree, unsigned int key, unsigned int info)
{
    Node *node = tree->root, *par = NULL;
    while (node)
    {
        if (node->key == key)
        {
            node->kmates = init_node(key, info, par);
            return 1;
        }
        par = node;
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    node = init_node(key, info, par);
    if (!par)
    {
        tree->root = node;
        return 0;
    }
    if (key < par->key)
        par->left = node;
    else
        par->right = node;
    node = find_scapegoat(tree, node);
    par = node ? node->parent : NULL;
    if (node)
    {
        Node *subtree = rebuild(node);
        if (!par)
        {
            tree->root = subtree;
            subtree->parent = NULL;
        }
        else
        {
            subtree->parent = par;
            (node == par->left) ? (par->left = subtree) : (par->right = subtree);
        }
    }
    return 0;
}

/*---Удаление----------------------------*/

int delete_node(Tree *tree, unsigned int key, int pos)
{
    Node *x = find_cert_node(tree->root, key, pos), *y = NULL;
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
        x->key = y->key;
        x->info = y->info;
    }
    free(y);

    /*калибровка + много конфигураций удаляемого, приколы со списками*/

    return 0;
}

/*---Обход----------------------------*/

void traversed_print(Node *node, unsigned int *border)
{
    if (!node)
        return;
    traversed_print(node->left, border);
    traversed_print(node->right, border);
    if ((border[0] <= node->key) && (node->key <= border[1]))
        printf("%u ", node->key);
}

int passage(Tree *tree, unsigned int *border)
{
    if (!tree->root)
        return 1;
    printf("Keys: ");
    traversed_print(tree->root, border);
    printf("\n");
    return 0;
}

/*---Специальный поиск----------------------------*/

Node *sfind_branch(Node *node, unsigned int key)
{
    Node *mstone = find_branch(node, key);
    if (mstone)
    {
        if (mstone->parent)
        {
            if (mstone == mstone->parent->left)
                return mstone->right ? find_min(mstone->right) : mstone->parent;
            if (find_min(mstone->right))
                return find_min(mstone->right);
            while (mstone->key <= key && mstone->parent)
                mstone = mstone->parent;
            if (mstone->key > key)
                return mstone;
            return NULL;
        }
        return mstone->right ? find_min(mstone->right) : NULL;
    }
    else
    {
        mstone = node;
        Node *ptr;
        while (mstone)
        {
            ptr = mstone;
            mstone = key < mstone->key ? mstone->left : mstone->right;
        }
        if (ptr->right)
            return ptr;
        while (ptr->key <= key && ptr->parent)
            ptr = ptr->parent;
        if (ptr->key > key)
            return ptr;
        return NULL;
    }
}

Array *sfind_node(Tree *tree, unsigned int key)
{
    Array *arr = (Array *)calloc(1, sizeof(Array));
    arr->ks = (Node **)calloc(1, sizeof(Node *));
    Node *branch = sfind_branch(tree->root, key);
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

/*---Выводы----------------------------*/

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

void print_tree(Node *node, int space)
{
    if (!node)
        return;
    space += 4;
    print_tree(node->right, space);
    printf("\n");
    for (int i = 4; i < space; i++)
        printf(" ");
    printf("%u\n", node->key);
    print_tree(node->left, space);
}

void graphviz(Node *node, FILE *fp, int *filler)
{
    if (!node)
        return;
    (*filler)++;
    fprintf(fp, "    %u;\n", node->key);
    if (node->left)
    {
        fprintf(fp, "    %u -> %u;\n", node->key, node->left->key);
        if (!node->right)
            fprintf(fp, "    %d [style=invis];\n    %u -> %d [style=invis];\n", *filler, node->key, *filler);
        graphviz(node->left, fp, filler);
    }
    if (node->right)
    {
        if (!node->left)
            fprintf(fp, "    %d [style=invis];\n    %u -> %d [style=invis];\n", *filler, node->key, *filler);
        fprintf(fp, "    %u -> %u;\n", node->key, node->right->key);
        graphviz(node->right, fp, filler);
    }
}