#ifndef LIB_H
#define LIB_H

typedef struct Node
{
    char *key;
    struct Node *left;
    struct Node *right;
    struct Node *next;
    struct Node *prev;
    struct Node *parent;
    unsigned int info;
} Node;

typedef struct Tree
{
    Node *root;
} Tree;

typedef struct SFind
{
    char *key;
    unsigned int info;
} SFind;

Tree *init();
unsigned int *find(Tree *, char *);
SFind *sfind_keys(Tree *, char *, int *);
int insert(Tree *, char *, unsigned int *);
int delete(Tree *, char *);
int search(Tree *, char *, char *);
void clear(Node *);
void printTree(Node *, int);

#endif