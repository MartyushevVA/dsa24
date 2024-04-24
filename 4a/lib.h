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
void clear(Node *);

int insert(Tree *, char *, unsigned int *);
int delete(Tree *, char *);
int search(Tree *, char *, char *);
unsigned int *find_info(Tree *, char *);
SFind *special_find(Tree *, char *, int *);
void format_print(Node *, int);
void graphviz(Node *, FILE *, int *);

#endif