#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"
#include "logic.h"

unsigned int stoui(char *str)
{
    unsigned int num = 0;
    for (int i = 0; str[i] && '0' <= str[i] && str[i] <= '9'; i++)
        num = num * 10 + (str[i] - '0');
    return num;
}

int dig(unsigned int num)
{
    if (!num)
        return 1;
    int i = 1;
    while (num /= 10)
        i++;
    return i;
}

int L_Add(Tree *tree, char *key, unsigned int info)
{
    if (insert(tree, key, &info))
    {
        printf("Value: %u ", info);
        return 1;
    }
    return 0;
}

int L_Delete(Tree *tree, char *key)
{
    return delete (tree, key);
}

int L_Search(Tree *tree, char *key_1, char *key_2)
{
    return search(tree, key_1, key_2);
}

int L_Find(Tree *tree, char *key)
{
    unsigned int *info = find_info(tree, key);
    if (!info)
        return 0;
    printf("Info: %u\n", *info);
    return 1;
}

int L_Special_Find(Tree *tree, char *key)
{
    int size = 0;
    SFind *arr = special_find(tree, key, &size);
    if (!size)
        return 0;
    for (int i = 0; i < size; i++)
        printf("Key: %s | Info: %u\n", (arr[i]).key, (arr[i]).info);
    free(arr);
    return 1;
}

void L_Format_Print(Tree *tree)
{
    format_print(tree->root, 0);
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
    char *buffer = (char *)calloc(1024, sizeof(char));
    unsigned int info = 0;
    char *key = NULL;
    int parity = 0;
    while (fscanf(file, "%s\n", buffer) == 1)
    {
        if (!parity)
        {
            key = (char *)calloc(strlen(buffer) + 1, sizeof(char));
            strcpy(key, buffer);
        }
        else
        {
            info = stoui(buffer);
            if (dig(info) != (int)strlen(buffer))
            {
                free(key);
                continue;
            }
            insert(tree, key, &info);
        }
        parity = (parity + 1) % 2;
    }
    fclose(file);
    free(buffer);
    if (!tree->root)
        return 2;
    return 0;
}

char **keygen(int size)
{
    char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char **keys = (char **)malloc(size * sizeof(char *));
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {

        int length = 5 + rand() % 25;
        keys[i] = (char *)calloc(length + 1, sizeof(char));
        for (int j = 0; j < length; j++)
            keys[i][j] = letters[rand() % 63];
    }
    return keys;
}
unsigned int *infogen(int size)
{
    unsigned int *infos = (unsigned int *)malloc(size * sizeof(unsigned int));
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {

        infos[i] = (unsigned)rand() % 1000000;
    }
    return infos;
}

int L_Timing()
{
    Tree *tree = init();
    clock_t begin, end;
    const int MAX_NUM = 1000000, MIN_NUM = 100000, step = 100000;
    const int num_of_res = (MAX_NUM - MIN_NUM) / step + 1;
    for (int num_of_elemts = MIN_NUM; num_of_elemts < MAX_NUM; num_of_elemts += step)
    {
        double t_insert = 0.0, t_find = 0.0, t_delete = 0.0;
        double insertions = 0.0, findings = 0.0, deletions = 0.0;
        for (int j = 0; j < 3 * num_of_res; j += 3)
        {
            char **keys = keygen(num_of_elemts);
            unsigned int *infos = infogen(num_of_elemts);
            begin = clock();
            for (int i = 0; i < num_of_elemts; i++)
                insert(tree, keys[i], &infos[i]);
            end = clock();
            t_insert = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < num_of_elemts; i++)
                find_info(tree, keys[i]);
            end = clock();
            t_find = (end - begin) / (CLOCKS_PER_SEC / 1000);
            begin = clock();
            for (int i = 0; i < num_of_elemts; i++)
                delete (tree, keys[i]);
            end = clock();
            t_delete = (end - begin) / (CLOCKS_PER_SEC / 1000);
            free(keys);
            free(infos);
            clear(tree->root);
            insertions += t_insert;
            findings += t_find;
            deletions += t_delete;
        }
        insertions /= num_of_res;
        findings /= num_of_res;
        deletions /= num_of_res;
        printf("Num of elements: %d\n Time on insert(): %f ms.\n Time on find(): %f ms.\n Time on delete(): %f ms.\n", num_of_elemts, insertions, findings, deletions);
    }
    free(tree);
    return 0;
}