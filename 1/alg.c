#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hfile.h"

int main()
{
    int N = 0, exit = 0;
    printf("Enter num of rows: ");
    if (input(&N))
        return 0;
    if (!N)
    {
        printf("OK\n");
        return 0;
    }
    Matr *matr = (Matr *)malloc(sizeof(Matr));
    matr->hight = N;
    matr->list = (Row *)malloc(N * sizeof(Row));
    for (int i = 0; i < matr->hight; i++)
    {
        exit = minput(matr, i);
        if (exit == 1)
        {
            freeing(matr, i);
            printf("Done\n");
            return 0;
        }
        if (exit == 2)
        {
            printf("Empty row (skipped)\n");
            i--;
            matr->hight--;
            matr->list = (Row *)realloc(matr->list, matr->hight * sizeof(Row));
        }
    }
    printf("Entered:\n");
    if (!matr->hight)
    {
        printf("Empty\nDone\n");
        free(matr->list);
        free(matr);
        return 0;
    }
    for (int i = 0; i < matr->hight; i++)
    {
        for (int j = 0; j < (matr->list)[i].width; j++)
            printf("%d ", (((matr->list)[i]).line)[j]);
        printf("\n");
    }
    Matr *new = (Matr *)malloc(sizeof(Matr));
    new->hight = 0;
    new->list = (Row *)malloc(matr->hight * sizeof(Row));
    for (int i = 0; i < matr->hight; i++)
        process(new, i, matr);
    printf("Result:\n");
    for (int i = 0; i < new->hight; i++)
    {
        for (int j = 0; j < (new->list)[i].width; j++)
            printf("%d ", (((new->list)[i]).line)[j]);
        printf("\n");
    }
    if (!new->hight)
        printf("Empty\n");
    freeing(matr, matr->hight);
    freeing(new, new->hight);
    printf("Done\n");
    return 0;
}