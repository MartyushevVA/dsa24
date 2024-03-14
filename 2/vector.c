#include <stdlib.h>
#include "lib.h"

typedef struct Stack
{
    int top;
    int allocated;
    char **list;
} Stack;

int check(Stack *stack)
{
    return size(stack) == stack->allocated;
}

void push(Stack *stack, char *elem)
{
    stack->top++;
    (stack->list)[stack->top] = elem;
}

char *pop(Stack *stack)
{
    char *a = (stack->list)[stack->top];
    stack->top--;
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