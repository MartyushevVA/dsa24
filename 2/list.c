#include <stdlib.h>
#include "lib.h"

typedef struct Item
{
    char *term;
    struct Item *next;
} Item;

typedef struct Stack
{
    Item *top;
} Stack;

int check(Stack *stack)
{
    return 0;
}

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

void freeing(Stack *stack)
{
    Item *ptr = stack->top;
    Item *temp;
    while (ptr)
    {
        free(ptr->term);
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
    free(stack);
}

Stack *init(int _)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    (*stack).top = NULL;
    return stack;
}