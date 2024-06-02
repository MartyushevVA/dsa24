#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

typedef struct Item
{
    int data;
    struct Item *next;
} Item;

typedef struct Queue
{
    Item *tail;
    Item *head;
} Queue;

Queue *init_queue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->tail = NULL;
    queue->head = NULL;
    return queue;
}

int q_is_empty(Queue *queue)
{
    return !queue->head;
}

void q_push(Queue *queue, int elem)
{
    Item *new = (Item *)malloc(sizeof(Item));
    new->data = elem;
    new->next = NULL;
    if (!queue->head)
    {
        queue->head = new;
        queue->tail = new;
    }
    else
    {
        queue->tail->next = new;
        queue->tail = new;
    }
}

int q_pop(Queue *queue)
{
    if (!queue->head)
        return -1;
    else
    {
        int data = queue->head->data;
        Item *ptr = queue->head;
        queue->head = ptr->next;
        free(ptr);
        return data;
    }
}

void remove_queue(Queue *queue)
{
    Item *ptr = queue->head;
    Item *temp;
    while (ptr)
    {
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
    free(queue);
}

Vertex *init_vertex(char *name, int sex, int born, int died)
{
    Vertex *elem = (Vertex *)calloc(1, sizeof(Vertex));
    elem->born = born;
    elem->died = died;
    elem->sex = sex;
    elem->name = (char *)calloc(strlen(name) + 1, sizeof(char));
    strcpy(elem->name, name);
    return elem;
}

Graph *init_graph()
{
    Graph *graph = (Graph *)calloc(1, sizeof(Graph));
    graph->ks = (Vertex **)calloc(50, sizeof(Vertex *));
    graph->msize = 50;
    return graph;
}

int get_hash(char *key)
{
    unsigned long hash = 0;
    int i = 0;
    while (key[i])
    {
        hash = hash * 17 + key[i];
        i++;
    }
    return hash;
}

void remove_graph(Graph *graph)
{
    if (!graph)
        return;
    Related *nprev = NULL;
    Related *temp = NULL;
    for (int i = 0; i < graph->msize; i++)
    {
        if (!graph->ks[i])
            continue;
        temp = graph->ks[i]->pair;
        nprev = NULL;
        while (temp)
        {
            nprev = temp;
            temp = temp->next;
            free(nprev);
        }
        free(graph->ks[i]->name);
        free(graph->ks[i]);
    }
    free(graph->ks);
    free(graph);
}

void print_array(Array *arr)
{
    for (int i = 0; i < arr->size; i++)
        printf("%s (%s): %d - %d\n", arr->space[i]->name, arr->space[i]->sex ? "F" : "M", arr->space[i]->born, arr->space[i]->died);
}

void remove_array(Array *arr)
{
    free(arr->space);
    free(arr);
}

int is_connected(Vertex *one, Vertex *another)
{
    Related *ptr = one->pair;
    while (ptr)
    {
        if (ptr->node == another)
            return 1;
        ptr = ptr->next;
    }
    return 0;
}

void f_insert(Vertex **arr, int size, Vertex *elem)
{
    int j = get_hash(elem->name);
    int i = 0;
    while (arr[(j + i) % size])
        i++;
    arr[(j + i) % size] = elem;
}

void smart_resize(Graph *graph, int new_msize)
{
    Vertex **new_ks = (Vertex **)calloc(new_msize, sizeof(Vertex *));
    for (int i = 0; i < graph->msize; i++)
        if (graph->ks[i])
            f_insert(new_ks, new_msize, graph->ks[i]);
    graph->msize = new_msize;
    free(graph->ks);
    graph->ks = new_ks;
}

int find(Graph *graph, char *name)
{
    int j = get_hash(name);
    int n = 0;
    while (graph->ks[(j + n) % graph->msize] && n < graph->msize)
    {
        if (strcmp(graph->ks[(j + n) % graph->msize]->name, name) == 0)
            return (j + n) % graph->msize;
        n++;
    }
    return -1;
}

int add_vertex(Graph *graph, char *name, int sex, int born, int died)
{
    if (find(graph, name) != -1)
        return 1;
    if (graph->csize > 0.5 * graph->msize)
        smart_resize(graph, 2 * graph->msize);
    Vertex *elem = init_vertex(name, sex, born, died);
    f_insert(graph->ks, graph->msize, elem);
    (graph->csize)++;
    return 0;
}

int add_edge(Graph *graph, char *name_1, char *name_2)
{
    int f = find(graph, name_1), s = find(graph, name_2);
    if (f == -1 || s == -1 || f == s)
        return 1;
    Vertex *one = graph->ks[f];
    Vertex *another = graph->ks[s];
    if (is_connected(one, another))
        return 2;
    Related *new = (Related *)malloc(sizeof(Related));
    new->node = another;
    new->next = one->pair;
    one->pair = new;
    new = (Related *)malloc(sizeof(Related));
    new->node = one;
    new->next = another->pair;
    another->pair = new;
    return 0;
}

int rm_vertex(Graph *graph, char *name)
{
    int e = find(graph, name);
    if (e == -1)
        return 1;
    Vertex *elem = graph->ks[e];
    graph->ks[e] = NULL;
    Related *ptr = elem->pair;
    Related *old = NULL;
    while (ptr)
    {
        Related *temp = ptr->node->pair, *prev = NULL;
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
            prev = temp;
            temp = temp->next;
        }
        old = ptr;
        ptr = ptr->next;
        free(old);
    }
    free(elem->name);
    free(elem);
    (graph->csize)--;
    if (graph->csize < 0.25 * graph->msize)
        smart_resize(graph, 0.5 * graph->msize);
    return 0;
}

int rm_edge(Graph *graph, char *name_1, char *name_2)
{
    int f = find(graph, name_1), s = find(graph, name_2);
    if (f == -1 || s == -1 || f == s)
        return 1;
    Vertex *one = graph->ks[f];
    Vertex *another = graph->ks[s];
    if (is_connected(one, another))
        return 2;
    Related *temp = one->pair, *prev = NULL;
    while (temp)
    {
        if (temp->node == another)
            break;
        prev = temp;
        temp = temp->next;
    }
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
    if (!prev)
        another->pair = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    return 0;
}

int sw_vertex(Graph *graph, char *name)
{
    int e = find(graph, name);
    if (e == -1)
        return 1;
    Vertex *elem = graph->ks[e];
    printf("%s (%s): %d - %d\n", elem->name, elem->sex ? "F" : "M", elem->born, elem->died);
    return 0;
}

int chng_vertex(Graph *graph, char *name_x, char *name_n, int sex, int born, int died)
{
    int e = find(graph, name_x);
    if (e == -1)
        return 1;
    Vertex *elem = graph->ks[e];
    graph->ks[e] = NULL;
    free(elem->name);
    elem->name = (char *)calloc(strlen(name_n) + 1, sizeof(char));
    strcpy(elem->name, name_n);
    elem->born = born;
    elem->died = died;
    elem->sex = sex;
    f_insert(graph->ks, graph->msize, elem);
    return 0;
}

void print_as_list(Graph *graph)
{
    Related *temp = NULL;
    for (int i = 0; i < graph->msize; i++)
    {
        if (!graph->ks[i])
            continue;
        printf("%s", graph->ks[i]->name);
        temp = graph->ks[i]->pair;
        while (temp)
        {
            printf(" --> %s", temp->node->name);
            temp = temp->next;
        }
        printf("\n");
    }
}

void print_graphviz(Graph *graph, FILE *fp)
{
    for (int i = 0; i < graph->msize; i++)
    {
        if (!graph->ks[i])
            continue;
        fprintf(fp, "    %s;\n", graph->ks[i]->name);
        for (int j = i; j < graph->msize; j++)
            if (is_connected(graph->ks[i], graph->ks[j]))
                fprintf(fp, "    %s -> %s [dir = none];\n", graph->ks[i]->born > graph->ks[j]->born ? graph->ks[j]->name : graph->ks[i]->name, graph->ks[i]->born > graph->ks[j]->born ? graph->ks[i]->name : graph->ks[j]->name);
    }
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

void remove_matrix(Matrix *matr)
{
    for (int i = 0; i < matr->size; i++)
        free(matr->field[i]);
    free(matr->field);
    free(matr->positions->space);
    free(matr->positions);
    free(matr);
}

Matrix *graph_to_matrix(Graph *graph)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->size = graph->csize;
    matrix->field = (int **)malloc(matrix->size * sizeof(int *));
    matrix->positions = (Array *)malloc(sizeof(Array));
    matrix->positions->size = matrix->size;
    matrix->positions->space = (Vertex **)malloc(matrix->size * sizeof(Vertex *));
    int pos = 0;
    for (int v = 0; v < graph->msize; v++)
    {
        if (graph->ks[v])
        {
            matrix->positions->space[pos] = graph->ks[v];
            matrix->field[pos] = (int *)calloc(matrix->size, sizeof(int));
            for (int j = 0; j < matrix->size; j++)
                matrix->field[pos][j] = 999999999;
            pos++;
        }
    }
    pos = 0;
    for (int v = 0; v < graph->msize; v++)
    {
        if (graph->ks[v])
        {
            matrix->field[pos][pos] = 0;
            Related *ptr = matrix->positions->space[pos]->pair;
            while (ptr)
            {
                matrix->field[pos][pointer_to_index(matrix->positions, ptr->node)] = 1;
                ptr = ptr->next;
            }
            pos++;
        }
    }
    if (!matrix->size)
    {
        remove_matrix(matrix);
        return NULL;
    }
    return matrix;
}

void common_to_spec(Matrix *matr)
{
    for (int i = 0; i < matr->size; i++)
        for (int j = 0; j < matr->size; j++)
            if (matr->positions->space[i]->born > matr->positions->space[j]->born)
                matr->field[i][j] = 999999999;
}

Array *breadth_first_search(Matrix *matr, char *name)
{
    int from = name_to_index(matr->positions, name);
    if (from == -1)
        return NULL;
    Queue *q = init_queue();
    Array *arr = (Array *)calloc(1, sizeof(Array));
    arr->space = (Vertex **)malloc(matr->size * sizeof(Vertex *));
    int *dist = (int *)malloc(matr->size * sizeof(int));
    for (int i = 0; i < matr->size; i++)
        dist[i] = 999999999;
    dist[from] = 0;
    Vertex *ptr = NULL;
    q_push(q, from);
    while (!q_is_empty(q))
    {

        int v = q_pop(q);
        if (v != from)
        {
            ptr = matr->positions->space[v];
            arr->space[arr->size] = ptr;
            (arr->size)++;
        }
        for (int i = 0; i < matr->size; i++)
            if (matr->field[v][i] != 999999999 && v != i)
                if (dist[i] == 999999999)
                {
                    dist[i] = dist[v] + 1;
                    q_push(q, i);
                }
    }
    arr->space = (Vertex **)realloc(arr->space, (arr->size) * sizeof(Vertex *));
    free(dist);
    remove_queue(q);
    return arr;
}

Array* dijkstra(Matrix *matr, char *name_1, char *name_2)
{
    int from = name_to_index(matr->positions, name_1);
    int to = name_to_index(matr->positions, name_2);
    if (from == -1 || to == -1)
        return NULL;
    int *dist = (int *)malloc(matr->size * sizeof(int));
    int *visited = (int *)calloc(matr->size, sizeof(int));
    int *prev = (int *)malloc(matr->size * sizeof(int));
    for (int i = 0; i < matr->size; i++)
    {
        dist[i] = 999999999;
        prev[i] = -1;
    }
    dist[from] = 0;
    for (int i = 0; i < matr->size; i++)
    {
        int nearest = -1;
        for (int v = 0; v < matr->size; v++)
            if (!visited[v] && (nearest == -1 || dist[nearest] > dist[v]))
                nearest = v;
        if (dist[nearest] == 999999999)
            break;
        visited[nearest] = 1;
        for (int k = 0; k < matr->size; k++)
            if (dist[k] > dist[nearest] + matr->field[nearest][k])
            {
                dist[k] = dist[nearest] + matr->field[nearest][k];
                prev[k] = nearest;
            }
    }
    Array *arr = (Array *)malloc(sizeof(Array));
    arr->size = dist[to] + 1;
    arr->space = (Vertex **)malloc(arr->size * sizeof(Vertex *));
    int k = dist[to];
    for (int i = to; i != -1; i = prev[i])
    {
        (arr->space)[k] = (matr->positions->space)[i];
        k--;
    }
    free(dist);
    free(visited);
    free(prev);
    return arr;
}

int count_of(Array *arr, int *dist, int size, int key)
{
    int k = 0;
    for (int i = 0; i < size; i++)
        if (dist[i] == key && (arr->space[i]->born > arr->space[i]->died))
            k++;
    return k;
}

int get_max(int *arr, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++)
        max = arr[i] > max ? (arr[i] == 999999999 ? max : arr[i]) : max;
    return max;
}

int *distribute(Matrix *matr, int **dist, char *name, int cash)
{
    int pos = name_to_index(matr->positions, name);
    if (pos == -1)
        return NULL;
    int maximum = get_max(dist[pos], matr->size);
    int *arr = (int *)calloc(maximum + 1, sizeof(int));
    double koef = 1;
    double sum = 0;
    for (int i = 1; i < maximum + 1; i++)
    {
        sum += koef * count_of(matr->positions, dist[pos], matr->size, i);
        koef /= 2;
    }
    sum = (double)cash / sum;
    koef = 1;
    for (int i = 1; i < maximum + 1; i++)
    {
        arr[i] = sum * koef;
        koef /= 2;
    }
    return arr;
}

void print_distr_array(Array *arr, int **dist, char *name, int *balance)
{
    int pos = name_to_index(arr, name);
    if (pos == -1)
        return;
    for (int i = 0; i < arr->size; i++)
        if (i != pos && dist[pos][i] != 999999999 && arr->space[i]->born > arr->space[i]->died)
            printf("%s: %d\n", arr->space[i]->name, balance[dist[pos][i]]);
}

int **floyd_warshall(Matrix *matr)
{
    int **dist = (int **)malloc(matr->size * sizeof(int *));
    for (int i = 0; i < matr->size; i++)
    {
        dist[i] = (int *)malloc(matr->size * sizeof(int));
        for (int j = 0; j < matr->size; j++)
            dist[i][j] = matr->field[i][j];
    }
    for (int v = 0; v < matr->size; v++)
        for (int a = 0; a < matr->size; a++)
            for (int b = 0; b < matr->size; b++)
                if (dist[a][v] != 999999999 && dist[v][b] != 999999999 &&
                    dist[a][b] > dist[a][v] + dist[v][b])
                    dist[a][b] = dist[a][v] + dist[v][b];
    return dist;
}