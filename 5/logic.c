#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"
#include "logic.h"

int L_Add_Vert(Graph *graph, char *name, int sex, int born, int died)
{
    int n = add_vertex(graph, name, sex, born, died);
    print_as_list(graph);
    L_Print_Graph(graph);
    return n;
}

int L_Add_Edge(Graph *graph, char *name_1, char *name_2)
{
    int n = add_edge(graph, name_1, name_2);
    print_as_list(graph);
    L_Print_Graph(graph);
    return n;
}

int L_Delete_Vert(Graph *graph, char *name)
{
    int n = rm_vertex(graph, name);
    print_as_list(graph);
    L_Print_Graph(graph);
    return n;
}

int L_Delete_Edge(Graph *graph, char *name_1, char *name_2)
{
    int n = rm_edge(graph, name_1, name_2);
    print_as_list(graph);
    L_Print_Graph(graph);
    return n;
}

int L_Change_Vert(Graph *graph, char *name_x, char *name_n, int sex, int born, int died)
{
    int n = chng_vertex(graph, name_x, name_n, sex, born, died);
    print_as_list(graph);
    L_Print_Graph(graph);
    return n;
}

int L_Print_List(Graph *graph)
{
    print_as_list(graph);
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
}

int L_Descendants(Graph *graph, char *name)
{
    Array *arr = breadth_first_search(graph, name);
    if (!arr)
        return 1;
    print_array(arr, 0);
    remove_array(arr);
    return 0;
}

int L_Min_Dist(Graph *graph, char *name_1, char *name_2)
{
    int n = dijkstra(graph, name_1, name_2);
    if (n == -1)
        return 1;
    printf("Relation degree: %d\n", n);
    return 0;
}

int L_Distribution(Graph *graph, char *name, int cash)
{
    int* dist = NULL;
    Array *arr = bellman_ford_algorithm(graph, name, &dist);
    if (!arr)
        return 1;
    int* distr = distribute(dist, arr->size, cash);
    print_distr_array(arr, dist, distr);
    remove_array(arr);
    free(distr);
    free(dist);
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
    fscanf(file, "\n");
    while (fscanf(file, "%s %s\n", nbuf, sname) == 2)
        add_edge(graph, sname, nbuf);
    free(nbuf);
    free(sname);
    fclose(file);
    return 0;
}

int L_Timing()
{
}

int L_Extra_Task(Graph *graph)
{
}

/*int L_Timing()
{
    clock_t begin, end;
    FILE *file = fopen("timing.txt", "w");
    fclose(file);
    const int MAX_NUM = 1000001, MIN_NUM = 25000, step = 25000, capacity = 20000;
    const int num_of_res = 20;
    Array *addit = set(capacity);
    Array *arr = set(MAX_NUM);
    for (int num_of_elemts = MIN_NUM; num_of_elemts < MAX_NUM; num_of_elemts += step)
    {
        file = fopen("timing.txt", "a");
        Tree *tree = init_tree();
        double insertions = 0.0, findings = 0.0, deletions = 0.0, sfindings = 0.0;
        for (int i = 0; i < num_of_elemts; i++)
            insert_node(tree, arr->ks[i]->key, arr->ks[i]->info);
        for (int j = 0; j < num_of_res; j++)
        {
            begin = clock();
            for (int i = 0; i < capacity; i++)
                insert_node(tree, addit->ks[i]->key, 1);
            end = clock();
            insertions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                L_Find(tree, addit->ks[i]->key, 1);
            end = clock();
            findings += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                delete_node(tree, addit->ks[i]->key, 10);
            end = clock();
            deletions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                L_Special_Find(tree, addit->ks[i]->key, 1);
            end = clock();
            sfindings += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
        }
        remove_tree(tree);
        insertions /= num_of_res;
        findings /= num_of_res;
        deletions /= num_of_res;
        sfindings /= num_of_res;
        printf("%d\n", num_of_elemts / step);
        fprintf(file, "%d %f %f %f %f\n", num_of_elemts, insertions / capacity, findings / capacity, deletions / capacity, sfindings / capacity);
        fclose(file);
    }
    remove_array(arr);
    remove_array(addit);
    return 0;
}*/