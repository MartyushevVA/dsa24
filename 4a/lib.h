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

typedef struct Elem
{
    char *key;
    unsigned int info;
} Elem;

Tree *init();
Elem *find(Tree *, char *);
unsigned int insert(Node **, char *, unsigned int);
int delete(Node **, char *);
int search(Tree *, char *, char *);

#endif