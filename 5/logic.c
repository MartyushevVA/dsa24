#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"
#include "logic.h"

int L_Add_Vert(Graph *graph, char *name, int sex, int born, int died)
{
    int n = add_vertex(graph, name, sex, born, died);
    return n;
}

int L_Add_Edge(Graph *graph, char *name_1, char *name_2)
{
    int n = add_edge(graph, name_1, name_2);
    return n;
}

int L_Delete_Vert(Graph *graph, char *name)
{
    int n = rm_vertex(graph, name);
    return n;
}

int L_Delete_Edge(Graph *graph, char *name_1, char *name_2)
{
    int n = rm_edge(graph, name_1, name_2);
    return n;
}

int L_Show_Vert(Graph *graph, char *name)
{
    int n = sw_vertex(graph, name);
    return n;
}

int L_Change_Vert(Graph *graph, char *name_x, char *name_n, int sex, int born, int died)
{
    int n = chng_vertex(graph, name_x, name_n, sex, born, died);
    return n;
}

int L_Print_List(Graph *graph)
{
    print_as_list(graph);
    return 0;
}

int L_Print_Graph(Graph *graph)
{
    FILE *file = fopen("graph.dot", "w");
    if (file)
    {
        fprintf(file, "digraph G {\n");
        print_graphviz(graph, file);
        fprintf(file, "}\n");
        fclose(file);
    }
    return 0;
}

int L_Descendants(Graph *graph, char *name)
{
    Matrix *matr = graph_to_matrix(graph);
    if (!matr)
        return 1;
    common_to_spec(matr);
    Array *arr = breadth_first_search(matr, name);
    remove_matrix(matr);
    if (!arr)
        return 2;
    print_array(arr);
    remove_array(arr);
    return 0;
}

int L_Min_Dist(Graph *graph, char *name_1, char *name_2)
{
    Matrix *matr = graph_to_matrix(graph);
    if (!matr)
        return 1;
    int n = dijkstra(matr, name_1, name_2);
    remove_matrix(matr);
    if (n == -1)
        return 2;
    printf("Relation degree: %d\n", n);
    return 0;
}

int L_Distribution(Graph *graph, char *name, int cash)
{
    Matrix *matr = graph_to_matrix(graph);
    if (!matr)
        return 1;
    common_to_spec(matr);
    int **dist = floyd_warshall(matr);
    int *balance = distribute(matr, dist, name, cash);
    if (!balance)
    {
        for (int i = 0; i < matr->size; i++)
            free(dist[i]);
        free(dist);
        remove_matrix(matr);
        return 2;
    }
    print_distr_array(matr->positions, dist, name, balance);
    for (int i = 0; i < matr->size; i++)
        free(dist[i]);
    free(dist);
    free(balance);
    remove_matrix(matr);
    return 0;
}

int L_Import(Graph *graph, char *fname)
{
    FILE *file = fopen(fname, "r");
    free(fname);
    if (!file)
        return 1;
    int buf[3];
    char *nbuf = (char *)calloc(1024, sizeof(char));
    char *sname = (char *)calloc(1024, sizeof(char));
    while (fscanf(file, "%s %d %d %d\n", nbuf, &buf[0], &buf[1], &buf[2]) == 4)
        add_vertex(graph, nbuf, buf[0], buf[1], buf[2]);
    while (fscanf(file, "%s %s\n", nbuf, sname) == 2)
        add_edge(graph, sname, nbuf);
    free(nbuf);
    free(sname);
    fclose(file);
    return 0;
}