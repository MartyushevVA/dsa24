#ifndef LIB_H
#define LIB_H

typedef struct Node
{
    unsigned int key, info;
    struct Node *left, *right, *parent, *kmates;
} Node;

typedef struct Tree
{
    float alpha;
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

Tree *init_tree();
void remove_tree(Tree *);
void remove_node(Node *);
Array *set(int);
void remove_array(Array *);
int print_array(Array *);

Array *find_node(Tree *, unsigned int);
int insert_node(Tree *, unsigned int, unsigned int);
int delete_node(Tree *, unsigned int, int);
int passage(Tree *, unsigned int *);
Array* sfind_node(Tree *, unsigned int);
void print_tree(Node *, int);
void graphviz(Node *, FILE *, int *);

#endif