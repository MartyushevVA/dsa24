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
    return delete(tree, key);
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
            free(key);
        }
        parity = (parity + 1) % 2;
    }
    fclose(file);
    free(buffer);
    if (!tree->root)
        return 2;
    return 0;
}

SFind *set(int size)
{
    char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(NULL));
    SFind *arr = (SFind *)malloc(size * sizeof(SFind));
    for (int i = 0; i < size; i++)
    {
        int length = 5 + rand() % 25;
        arr[i].key = (char *)calloc(length + 1, sizeof(char));
        for (int j = 0; j < length; j++)
            (arr[i].key)[j] = letters[rand() % 63];
        arr[i].info = rand() % 1000000;
    }
    return arr;
}

SFind *some(SFind* src, int size, int new_size)
{
    srand(time(NULL));
    SFind *arr = (SFind *)malloc(new_size * sizeof(SFind));
    for (int i=0; i<new_size; i++)
    {
        int ind = rand() % size;
        arr[i].info = src[i].info;
        arr[i].key = strdup(src[i].key);
    }
    return arr;
}

void sf_clear(SFind* arr, int size)
{
    for (int i=0; i<size; i++)
        free(arr[i].key);
    free(arr);
}

int L_Timing()
{
    Tree *tree = init();
    clock_t begin, end;
    const int MAX_NUM = 1000000, MIN_NUM = 100000, step = 100000, capacity = 10000;
    const int num_of_res = 25;
    for (int num_of_elemts = MIN_NUM; num_of_elemts < MAX_NUM; num_of_elemts += step)
    {
        double insertions = 0.0, findings = 0.0, deletions = 0.0;
        for (int j = 0; j < num_of_res; j++)
        {
            int inserted = 0, found = 0, deleted = 0;
            SFind *arr = set(num_of_elemts);
            for (int i = 0; i < num_of_elemts; i++)
                insert(tree, arr[i].key, &(arr[i].info));
            // дерево заполнено

            // замер вставки
            SFind* temp = set(capacity);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                if (!insert(tree, temp[i].key, &(temp[i].info)))
                    inserted++;
            end = clock();
            insertions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            sf_clear(temp, capacity);
            
            // замер поиска
            temp = some(arr, num_of_elemts, capacity);
            begin = clock();
            for (int i = 0; i < capacity; i++)
                if (find_info(tree, temp[i].key))
                    found++;
            end = clock();
            findings += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            sf_clear(temp, capacity);

            // замер удаления
            temp = some(arr, num_of_elemts, capacity);printf("F");
            begin = clock();
            for (int i = 0; i < capacity; i++)
                if (!delete(tree, temp[i].key))
                    deleted++;
            end = clock();
            deletions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            sf_clear(temp, capacity);
            sf_clear(arr, num_of_elemts);
            clear(tree->root);
        }
        insertions /= num_of_res;
        findings /= num_of_res;
        deletions /= num_of_res;
        printf("Num of elements: %d\n Time on insert(): %f ms.\n Time on find(): %f ms.\n Time on delete(): %f ms.\n", num_of_elemts, insertions, findings, deletions);
    }
    free(tree);
    return 0;
}