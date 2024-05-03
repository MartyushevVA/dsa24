#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

/*---Инициализация и очистка----------------------------*/

Node *init_node(unsigned int key, unsigned int info, Node* parent)
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
    tree->alpha = 0.5;
    return tree;
}


void remove_tree(Tree* tree)
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
        //free(arr->ks[i]);
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

Node *flatten_tree(Node *node, Node *head)
{
    if (!node)
        return head;
    node->right = flatten_tree(node->right, head);
    return flatten_tree(node->left, node);
}

Node *build_height_balanced_tree(int size, Node *head)
{
    if (size == 1)
        return head;
    else if (size == 2)
    {
        head->right->left = head;
        return head->right;
    }
    Node *root = (build_height_balanced_tree((size - 1) / 2, head))->right;
    Node *last = build_height_balanced_tree((size - 1) / 2, root->right);
    root->left = head;
    return last;
}

Node *rebuild_tree(int size, Node *scapegoat)
{
    Node *head = flatten_tree(scapegoat, NULL);
    build_height_balanced_tree(size, head);
    while (head->parent)
        head = head->parent;
    return head;
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
            node->kmates->left = node->left;
            node->kmates->right = node->right;
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
    
    /*калибровка*/

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

int passage(Tree *tree, unsigned int begin, unsigned int end)
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
    printf("%s %u\n", node->key);
    print_tree(node->left, space);
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