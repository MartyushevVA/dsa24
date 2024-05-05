#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"
#include "logic.h"

int L_Add(Tree *tree, unsigned int key, unsigned int info)
{
    int n = insert_node(tree, key, info);
    L_GraphViz_Print(tree);
    return n;
}

int L_Delete(Tree *tree, unsigned int key, int pos)
{
    int n = delete_node(tree, key, pos);
    L_GraphViz_Print(tree);
    return n;
}

int L_Passage(Tree *tree, unsigned int *border)
{
    return passage(tree, border);
}

int L_Find(Tree *tree, unsigned int key)
{
    Array *arr = find_node(tree, key);
    return print_array(arr);
}

int L_Special_Find(Tree *tree, unsigned int key)
{
    Array *arr = sfind_node(tree, key);
    return print_array(arr);
}

void L_Format_Print(Tree *tree)
{
    print_tree(tree->root, 0);
}

void L_GraphViz_Print(Tree *tree)
{
    FILE *file = fopen("graph.dot", "w");
    int filler = 0;
    if (file)
    {
        fprintf(file, "digraph G {\n");
        graphviz(tree->root, file, &filler);
        fprintf(file, "}\n");
        fclose(file);
    }
}

int L_Import(Tree *tree, char *fname)
{
    FILE *file = fopen(fname, "r");
    free(fname);
    if (!file)
        return 1;
    remove_node(tree->root);
    unsigned int buf[2];
    while (fscanf(file, "%u\n%u", &buf[0], &buf[1]) == 2)
        insert_node(tree, buf[0], buf[1]);
    fclose(file);
    if (!tree->root)
        return 2;
    L_GraphViz_Print(tree);
    return 0;
}

int L_Timing()
{
    clock_t begin, end;
    const int MAX_NUM = 2000001, MIN_NUM = 100000, step = 100000, capacity = 100000;
    const int num_of_res = 25;
    for (int num_of_elemts = MIN_NUM; num_of_elemts < MAX_NUM; num_of_elemts += step)
    {
        double insertions = 0.0, findings = 0.0, deletions = 0.0;
        Tree *tree = init_tree();
        Array *arr = set(num_of_elemts);
        for (int i = 0; i < num_of_elemts; i++)
            insert_node(tree, arr->ks[i]->key, arr->ks[i]->info);
        remove_array(arr);
        for (int j = 0; j < num_of_res; j++)
        {
            printf(".");
            Array *addit = set(capacity);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                insert_node(tree, addit->ks[i]->key, addit->ks[i]->info);
            end = clock();
            insertions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                find_node(tree, addit->ks[i]->key);
            end = clock();
            findings += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                delete_node(tree, addit->ks[i]->key, 0);
            end = clock();
            deletions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            remove_array(addit);
        }
        remove_tree(tree);
        insertions /= num_of_res;
        findings /= num_of_res;
        deletions /= num_of_res;
        printf("\nNum of elements: %d\n Time on insert(): %f ms.\n Time on find(): %f ms.\n Time on delete(): %f ms.\n", num_of_elemts, insertions/num_of_elemts, findings/num_of_elemts, deletions/num_of_elemts);
    }
    return 0;
}