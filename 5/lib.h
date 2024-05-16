#ifndef LIB_H
#define LIB_H

typedef struct Vertex
{
    char *name;
    int sex, born, died;
    Vertex *next;
} Vertex;

typedef struct Graph
{
    int quantity;
    Vertex *space;
} Graph;

void remove_graph(Graph *graph);
Graph *init_graph();

#endif