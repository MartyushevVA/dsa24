#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hfile_l.h"

void push(Stack *stack, char *elem)
{
    Item *item = (Item *)malloc(sizeof(Item));
    (*item).term = elem;
    (*item).next = (*stack).top;
    (*stack).top = item;
}

char *pop(Stack *stack)
{
    char *str = NULL;
    Item *item = (*stack).top;
    (*stack).top = (*item).next;
    str = (*item).term;
    free(item);
    return str;
}

int size(Stack *stack)
{
    int len = 0;
    Item *ptr = stack->top;
    while (ptr)
    {
        len++;
        ptr = ptr->next;
    }
    return len;
}

void freeing(Stack* stack)
{
    Item *ptr = stack->top;
    while (ptr)
    {
        free(ptr->term);
        free(ptr);
        ptr = ptr->next;
    }
    free(stack);
}

Stack* init()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    (*stack).top = NULL;
    return stack;
}