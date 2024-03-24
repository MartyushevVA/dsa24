#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

int input(int *X)
{
    int check = scanf("%d", X);
    while (check != 1 || *X < 0)
    {
        if (check == EOF)
            return 1;
        if (*X < 0)
            printf("Can't be <0: ");
        check = scanf("%d", X);
    }
    scanf("%*c");
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