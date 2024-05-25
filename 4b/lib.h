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
    int weight, maxweight;
    Node *root;
} Tree;

typedef struct Array
{
    Node **ks;
    int size;
} Array;

Tree *init_tree();
void remove_tree(Tree *);
void remove_node(Node *);
Array *set(int, int);
void remove_array(Array *);
int print_array(Array *);

int insert_node(Tree *, unsigned int, unsigned int);
int delete_node(Tree *, unsigned int, int);
Array *find_node(Tree *, unsigned int);
Array* sfind_node(Tree *, unsigned int);
int passage(Tree *, unsigned int *);
void print_tree(Node *, int);
void graphviz(Node *, FILE *, int *);

unsigned int* get_branch_info(Tree*, unsigned int, int*);

#endif