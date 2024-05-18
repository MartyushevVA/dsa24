#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

Vertex *init_vertex(char *name, int sex, int born, int died)
{
    Vertex *elem = (Vertex *)calloc(1, sizeof(Vertex));
    elem->born = born;
    elem->died = died;
    elem->sex = sex;
    elem->name = (char *)calloc(strlen(name) + 1, sizeof(char));
    strcpy(elem->name, name);
    free(name);
    return elem;
}

Graph *init_graph()
{
    Graph *graph = (Graph *)calloc(1, sizeof(Graph));
    return graph;
}

Vertex *find_by_name(Graph *graph, Vertex **previos, char *name)
{
    Vertex *ptr = graph->head;
    while (ptr)
    {
        if (strcmp(ptr->name, name) == 0)
            return ptr;
        (*previos) = ptr;
        ptr = ptr->next;
    }
    return NULL;
}

int is_connected(Vertex *one, Vertex *another)
{
    Nbors *ptr = one->pair;
    while (ptr)
    {
        if (ptr->node == another)
            return strcmp(ptr->node->name, another->name);
        ptr = ptr->next;
    }
    return 0;
}

int add_vertex(Graph *graph, char *name, int sex, int born, int died)
{
    Vertex *elem = init_vertex(name, sex, born, died);
    Vertex *ptr = graph->head;
    if (!ptr)
    {
        graph->head = elem;
        return 0;
    }
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = elem;
    return 0;
}

int add_edge(Graph *graph, char *name_1, char *name_2)
{
    Vertex *one = NULL, *another = NULL, *ptr = graph->head;
    while (ptr)
    {
        if (strcmp(ptr->name, name_1) == 0)
            one = ptr;
        if (strcmp(ptr->name, name_2) == 0)
            another = ptr;
        ptr = ptr->next;
    }
    if (!one || !another || one == another)
        return 1;
    Nbors *new = (Nbors *)malloc(sizeof(Nbors));
    new->node = another;
    new->next = one->pair;
    one->pair = new;
    new = (Nbors *)malloc(sizeof(Nbors));
    new->node = one;
    new->next = another->pair;
    another->pair = new;
    return 0;
}

int rm_vertex(Graph *graph, char *name)
{
    Vertex *previos = NULL;
    Vertex *elem = find_by_name(graph, &previos, name);
    if (!elem)
        return 1;
    Nbors *ptr = elem->pair;
    Nbors *old = NULL;
    while (ptr)
    {
        Nbors *temp = ptr->node->pair, *prev = NULL;
        while (temp)
        {
            if (strcmp(temp->node->name, name) == 0)
            {
                if (!prev)
                    ptr->node->pair = ptr->node->pair->next;
                else
                    prev->next = temp->next;
                free(temp);
                break;
            }
            prev = ptr;
            ptr = ptr->next;
        }
        old = ptr;
        ptr = ptr->next;
        free(old);
    }
    free(elem->name);
    if (!previos)
        graph->head = elem->next;
    else
        previos->next = elem->next;
    free(elem);
    return 0;
}

int rm_edge(Graph *graph, char *name_1, char *name_2)
{
    Vertex *one = NULL, *another = NULL, *ptr = graph->head;
    while (ptr)
    {
        if (strcmp(ptr->name, name_1) == 0)
        {
            one = ptr;
            if (another)
                break;
        }
        if (strcmp(ptr->name, name_2) == 0)
        {
            another = ptr;
            if (one)
                break;
        }
        ptr = ptr->next;
    }
    if (!one || !another || one == another)
        return 1;
    Nbors *temp = one->pair, *prev = NULL;
    while (temp)
    {
        if (temp->node == another)
            break;
        prev = temp;
        temp = temp->next;
    }
    if (temp->node != another)
        return 1;
    if (!prev)
        one->pair = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    temp = another->pair, prev = NULL;
    while (temp)
    {
        if (temp->node == one)
            break;
        prev = temp;
        temp = temp->next;
    }
    if (temp->node != one)
        return 1;
    if (!prev)
        another->pair = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    return 0;
}

int chng_vertex(Graph *graph, char *name_x, char *name_n, int sex, int born, int died)
{
    Vertex *trash, *elem = find_by_name(graph, &trash, name_x);
    if (!elem)
        return 1;
    free(elem->name);
    elem->name = (char *)calloc(strlen(name_n) + 1, sizeof(char));
    strcpy(elem->name, name_n);
    elem->born = born;
    elem->died = died;
    elem->sex = sex;
}

void print_as_list(Graph *graph)
{
    Vertex *ptr = graph->head;
    Nbors *temp = NULL;
    while (ptr)
    {
        printf("%s", ptr->name);
        temp = ptr->pair;
        while (temp)
        {
            printf(" --> %s", temp->node->name);
            temp = temp->next;
        }
        ptr = ptr->next;
        printf("\n");
    }
}

void print_graphviz(Graph *graph, FILE *fp)
{
    Vertex *ptr = graph->head, *temp = NULL;
    if (!ptr)
        return;
    while (ptr)
    {
        temp = ptr->next;
        fprintf(fp, "    %s;\n", ptr->name);
        while (temp)
        {
            if (is_connected(ptr, temp) > 0)
                fprintf(fp, "    %s -> %s;\n", ptr->name, temp->name);
            temp = temp->next;
        }
        ptr = ptr->next;
    }
}

int get_size(Graph *graph)
{
    int size = 0;
    Vertex *ptr = graph->head;
    while (ptr)
    {
        size++;
        ptr = ptr->next;
    }
    return size;
}

int pointer_to_index(Array *arr, Vertex *ver)
{
    for (int i = 0; i < arr->size; i++)
        if (arr->space[i] == ver)
            return i;
    return -1;
}

int name_to_index(Array *arr, char *name)
{
    for (int i = 0; i < arr->size; i++)
        if (strcmp(arr->space[i]->name, name) == 0)
            return i;
    return -1;
}

Vertex *index_to_pointer(Array *arr, int index)
{
    return arr->space[index];
}

int is_name_in_list(Array *arr, char *name)
{
    return name_to_index(arr, name) != -1;
}

Matrix *graph_to_matrix(Graph *graph)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->size = get_size(graph);
    matrix->field = (int **)malloc(matrix->size * sizeof(Array));
    matrix->positions = (Array *)malloc(sizeof(Array));
    matrix->positions->size = matrix->size;
    matrix->positions->space = (Vertex **)malloc(matrix->size * sizeof(Vertex *));
    Vertex *ptr = graph->head;
    for (int i = 0; i < matrix->size; i++)
    {
        matrix->positions->space[i] = ptr;
        ptr = ptr->next;
        matrix->field[i] = (int *)calloc(matrix->size, sizeof(int));
    }
    for (int i = 0; i < matrix->size; i++)
        for (int j = 0; j < matrix->size; j++)
        {
            if (i != j)
            {
                if (is_connected(matrix->positions->space[i], matrix->positions->space[j]))
                    matrix->field[i][j] = 1;
                else
                    matrix->field[i][j] = 99999;
            }
        }
    return matrix;
}

int breadth_first_search(Graph *graph, char *name)
{
    Matrix *matr = graph_to_matrix(graph);
    int dist = (int *)calloc(matr->size, sizeof(int));
}

int dijkstra(Graph *graph, char *name_1, char *name_2)
{
    Matrix *matr = graph_to_matrix(graph);
    int *dist = (int *)calloc(matr->size, sizeof(int));
    if (!is_name_in_list(matr->positions, name_1) || !is_name_in_list(matr->positions, name_2))
        return -1;
    int start = name_to_index(matr->positions, name_1);
    for (int i = 0; i < matr->size; i++)
        if (i != start)
            dist[i] = 99999;
    int *visited = (int *)calloc(matr->size, sizeof(int));
    for (int i = 0; i < matr->size; i++)
    {
        int nearest = -1;
        for (int j = 0; j < matr->size; j++)
        {
            if (!visited[j] && (nearest == -1 || dist[nearest] > dist[j]))
                nearest = j;
        }
        if (dist[nearest] > 9999)
            break;
        visited[nearest] = 1;
        for (int k = 0; k < matr->size; k++)
            if (dist[matr->field[i][k]] > dist[nearest] + matr->field[nearest][k])
                dist[matr->field[i][k]] = dist[nearest] + matr->field[nearest][k];
    }
    // каскадные чистки
    return dist[name_to_index(matr->positions, name_2)];
}

int bellman_ford_algorithm(Graph *graph, char *name, int cash)
{
    Matrix *matr = graph_to_matrix(graph);
    int dist = (int *)calloc(matr->size, sizeof(int));
}
