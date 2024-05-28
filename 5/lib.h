#ifndef LIB_H
#define LIB_H

typedef struct Related
{
    struct Vertex *node;
    struct Related *next;
} Related;

typedef struct Vertex
{
    char *name;
    int sex, born, died;
    Related *pair;
} Vertex;

typedef struct Graph
{
    Vertex **ks;
    int msize;
    int csize;
} Graph;

typedef struct Array
{
    int size;
    Vertex **space;
} Array;

typedef struct Matrix
{
    int size;
    Array*positions;
    int **field;
} Matrix;

void remove_graph(Graph *);
Graph *init_graph();
void print_array(Array *);
void remove_array(Array *);
int *distribute(Matrix *, int **, char *, int);
void print_distr_array(Array *, int **, char *, int *);

int add_vertex(Graph *, char *, int, int, int);
int add_edge(Graph *, char *, char *);
int rm_vertex(Graph *, char *);
int rm_edge(Graph *, char *, char *);
int sw_vertex(Graph *, char *);
int chng_vertex(Graph *, char *, char *, int, int, int);
void print_as_list(Graph *);
void print_graphviz(Graph *, FILE *);

void common_to_spec(Matrix *);
Matrix *graph_to_matrix(Graph *);
void remove_matrix(Matrix *);
Array *breadth_first_search(Matrix *, char *);
int dijkstra(Matrix *, char *, char *);
int **floyd_warshall(Matrix *);

#endif