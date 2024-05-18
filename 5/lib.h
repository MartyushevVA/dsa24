#ifndef LIB_H
#define LIB_H

typedef struct Nbors
{
    struct Vertex *node;
    Nbors *next;
} Nbors;

typedef struct Vertex
{
    char *name;
    int sex, born, died;
    Nbors *pair;
    Vertex *next;
} Vertex;

typedef struct Graph
{
    Vertex *head;
} Graph;

void remove_graph(Graph *);
Graph *init_graph();

int add_vertex(Graph *, char *, int, int, int);
int add_edge(Graph *, char *, char *);
int rm_vertex(Graph *, char *);
int rm_edge(Graph *, char *, char *);
int chng_vertex(Graph *, char *, char *, int, int, int);
void print_as_list(Graph *);
void print_graphviz(Graph *, FILE *);

int breadth_first_search(graph, name);
int dijkstra(graph, name_1, name_2);
int bellman_ford_algorithm(graph, name, cash);

#endif