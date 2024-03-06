#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "hfile_l.h"
#include "hfile_v.h"

char *process(char *src, int allocated)
{
    Stack *stack = init(allocated);
    char *new;
    int i = 0;
    char symb;
    while (src[i])
    {
        symb = src[i];
        if ((symb >= 'a' && symb <= 'z') || (symb >= 'A' && symb <= 'Z') || (symb >= '0' && symb <= '9'))
        {
            if (check(stack))
            {
                freeing(stack);
                return NULL;
            }
            char *let = (char *)calloc(2, sizeof(char));
            let[0] = symb;
            push(stack, let);
        }
        if (symb == '+' || symb == '-' || symb == '*' || symb == '/')
        {
            if (size(stack) < 2)
            {
                freeing(stack);
                return NULL;
            }
            char *first = pop(stack);
            char *second = pop(stack);
            char *temp = NULL;
            if (strlen(first) > 1)
            {
                temp = (char *)calloc(strlen(first) + 3, sizeof(char));
                strcat(temp, "(");
                strcat(temp, first);
                strcat(temp, ")");
                free(first);
                first = temp;
            }
            if (strlen(second) > 1)
            {
                temp = (char *)calloc(strlen(second) + 3, sizeof(char));
                strcat(temp, "(");
                strcat(temp, second);
                strcat(temp, ")");
                free(second);
                second = temp;
            }
            temp = (char *)calloc(strlen(first) + strlen(second) + 2, sizeof(char));
            strcat(temp, second);
            free(second);
            char *let = (char *)calloc(2, sizeof(char));
            let[0] = symb;
            strcat(temp, let);
            free(let);
            strcat(temp, first);
            free(first);
            push(stack, temp);
        }
        i++;
    }
    if (size(stack) != 1)
    {
        freeing(stack);
        return NULL;
    }
    new = pop(stack);
    freeing(stack);
    return new;
}