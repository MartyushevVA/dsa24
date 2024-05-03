#ifndef LIB_H
#define LIB_H

typedef struct Node
{
    unsigned int key, info;
    struct Node *left, *right, *parent, *kmates;
} Node;

typedef struct Tree
{
    int size, max_size;
    Node *root;
} Tree;

typedef struct Array
{
    Node **ks;
    int size;
} Array;

typedef struct Elems
{
    unsigned int key, info;
} Elems;

Tree *init();
void clear(Node *);

int print_array(Array *);
Array *finding(Tree *, unsigned int);

int insert(Tree *, unsigned int, unsigned int *);

int delete(Tree *, unsigned int);

int search(Tree *, unsigned int, unsigned int);

SFind *special_find(Tree *, unsigned int, int *);

void format_print(Node *, int);

void graphviz(Node *, FILE *, int *);

#endif