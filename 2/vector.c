#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hfile_v.h"

int check(Stack *stack)
{
    return size(stack) == stack->allocated;
}

void push(Stack *stack, char *elem)
{
    stack->top++;
    // stack->list = (char **)realloc(stack->list, (stack->top + 1) * sizeof(char *));
    (stack->list)[stack->top] = elem;
}

char *pop(Stack *stack)
{
    char *a = (stack->list)[stack->top];
    stack->top--;
    /*if (stack->top > -1)
        stack->list = (char **)realloc(stack->list, (stack->top + 1) * sizeof(char *));*/
    return a;
}

int size(Stack *stack)
{
    return stack->top + 1;
}

void freeing(Stack *stack)
{
    for (int i = 0; i < stack->top + 1; i++)
        free((stack->list)[i]);
    free(stack->list);
    free(stack);
}

Stack *init(int allocated)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    stack->list = (char **)calloc(allocated + 1, sizeof(char *));
    stack->allocated = allocated;
    return stack;
}