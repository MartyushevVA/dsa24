#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"
#include "logic.h"

int L_Add(Tree *tree, unsigned int key, unsigned int info)
{
    int n = insert_node(tree, key, info);
    return n;
}

int L_Delete(Tree *tree, unsigned int key, int pos)
{
    int n = delete_node(tree, key, pos);
    return n;
}

int L_Passage(Tree *tree, unsigned int *border)
{
    return passage(tree, border);
}

int L_Find(Tree *tree, unsigned int key, int mode)
{
    Array *arr = find_node(tree, key);
    if (mode)
    {
        remove_array(arr);
        return 0;
    }
    return print_array(arr);
}

int L_Special_Find(Tree *tree, unsigned int key, int mode)
{
    Array *arr = sfind_node(tree, key);
    if (mode)
    {
        remove_array(arr);
        return 0;
    }
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
    return 0;
}

int L_Timing()
{
    clock_t begin, end;
    FILE *file = fopen("timing.txt", "w");
    fclose(file);
    const int MAX_NUM = 1000001, MIN_NUM = 100000, step = 100000, capacity = 10000;
    const int num_of_res = 1;
    Tree *tree = init_tree();
    for (int num_of_elemts = MIN_NUM; num_of_elemts < MAX_NUM; num_of_elemts += step)
    {
        file = fopen("timing.txt", "a");
        double insertions = 0.0, findings = 0.0, deletions = 0.0, sfindings = 0.0;
        Array *arr = set(num_of_elemts, num_of_elemts);
        for (int i = 0; i < step; i++)
            insert_node(tree, arr->ks[i]->key, arr->ks[i]->info);
        remove_array(arr);
        for (int j = 0; j < num_of_res; j++)
        {
            printf(".");
            Array *addit = set(capacity, num_of_elemts);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                L_Add(tree, addit->ks[i]->key, 1);
            end = clock();
            insertions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                L_Find(tree, addit->ks[i]->key, 1);
            end = clock();
            findings += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                L_Delete(tree, addit->ks[i]->key, 0);
            end = clock();
            deletions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                L_Special_Find(tree, addit->ks[i]->key, 1);
            end = clock();
            sfindings += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            remove_array(addit);
        }
        remove_node(tree->root);
        insertions /= num_of_res;
        findings /= num_of_res;
        deletions /= num_of_res;
        sfindings /= num_of_res;
        printf("%d\n", num_of_elemts / step);
        fprintf(file, "%d %f %f %f %f\n", num_of_elemts, insertions / capacity, findings / capacity, deletions / capacity, sfindings / capacity);
        fclose(file);
    }
    return 0;
}

int L_Add_Task(char *fname, unsigned int key)
{
    FILE *file = fopen(fname, "r");
    free(fname);
    if (!file)
        return 1;
    Tree *tree = init_tree();
    unsigned int num_of_string = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ", ");
        while (token)
        {
            insert_node(tree, atoi(token), num_of_string);
            token = strtok(NULL, ", ");
        }
        num_of_string++;
    }
    fclose(file);
    int size = 0;
    unsigned int *arr = get_branch_info(tree, key, &size);
    printf("Found in rows: ");
    unsigned int last = 9999;
    for (int i = 0; i < size; i++)
        if (arr[i] != last)
        {
            last = arr[i];
            printf("%u ", arr[i]);
        }
    printf("\n");
    free(arr);
    remove_tree(tree);
    return 0;
}