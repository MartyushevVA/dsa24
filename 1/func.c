#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hfile.h"

int dig(int a)
{
    if (a == 0)
        return 1;
    if (a < 0)
        a *= (-1);
    int k = 0;
    while (a)
    {
        k++;
        a /= 10;
    }
    return k;
}

int check(int X, int size, int *mas)
{
    int avnum = 0;
    for (int i = 0; i < size; i++)
        avnum += dig(mas[i]);
    avnum /= size;
    return dig(X) > avnum;
}

int input(int *X)
{
    int check = scanf("%d", X);
    while (check != 1 || *X < 0)
    {
        if (check == EOF)
            return 1;
        if (*X < 0)
            printf("Can't be <0: ");
        scanf("%*[^\n]");
        check = scanf("%d", X);
    }
    return 0;
}

char *readline(char *PROMPT)
{
    char *word = (char *)malloc(2 * sizeof(char));
    char symb = 0;
    int curr = 0, ggg = 0, test = 1;
    printf("%s", PROMPT);
    while (test)
    {
        test = scanf("%1[^\n]", &symb);
        if (test == EOF)
        {
            free(word);
            return NULL;
        }
        word[ggg] = symb;
        curr++;
        ggg++;
        word = (char *)realloc(word, (ggg + 1) * sizeof(char));
    }
    word[ggg - 1] = 0;
    scanf("%*c");
    return word;
}

int *row(int *size)
{
    int *arr = (int *)calloc(*size, sizeof(int));
    int num = 0, count = 0;
    scanf("%*[\n]");
    char *string = readline("");
    if (string == NULL)
    {
        free(arr);
        return NULL;
    }
    char *token = strtok(string, " ");
    int next = 0;
    while (token && (count < *size))
    {
        char *word = (char *)calloc(strlen(token) + 1, sizeof(char));
        strcpy(word, token);
        int neg = 0;
        if (word[0] == '-')
            neg = 1;
        for (int i = neg; i < strlen(word); i++)
        {
            if (word[i] < '0' || word[i] > '9')
            {
                next = 1;
                break;
            }
            else
            {
                if (num > 0)
                    num = num * 10 + (word[i] - 48);
                else if (num < 0)
                    num = num * 10 - (word[i] - 48);
                else
                {
                    if (!neg)
                    {
                        num = word[i] - 48;
                    }
                    else
                    {
                        num = 48 - word[i];
                    }
                }
            }
        }
        if (!next)
        {
            arr[count] = num;
            count++;
        }
        num = 0;
        next = 0;
        free(word);
        token = strtok(NULL, " ");
    }
    free(string);
    *size = count;
    if (*size)
    {
        arr = (int *)realloc(arr, *size * sizeof(int));
        return arr;
    }
    else
    {
        free(arr);
        int *a;
        *a = 0;
        return a;
    }
}

int minput(Matr *matr, int i)
{
    int M = 0;
    printf("Enter length of %d row: ", i + 1);
    if (input(&M))
        return 1;
    if (M == 0)
        return 2;
    printf("Enter row: ");
    int *mas = row(&M);
    if (mas == NULL)
        return 2;
    ((matr->list)[i]).line = mas;
    ((matr->list)[i]).width = M;
    return 0;
}

void process(Matr *new, int i, Matr *matr)
{
    int *mas = (int *)malloc(sizeof(int));
    int M = 0;
    for (int j = 0; j < ((matr->list)[i]).width; j++)
        if (check((((matr->list)[i]).line)[j], ((matr->list)[i]).width, ((matr->list)[i]).line))
        {
            M++;
            mas = (int *)realloc(mas, M * sizeof(int));
            mas[M - 1] = (((matr->list)[i]).line)[j];
        }
    if (M != 0)
    {
        ((new->list)[new->hight]).line = mas;
        ((new->list)[new->hight]).width = M;
        (new->hight)++;
    }
    else
    {
        free(mas);
    }
}

void freeing(Matr *matr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (((matr->list)[i]).line)
            free(((matr->list)[i]).line);
    }
    free(matr->list);
    free(matr);
}