#ifndef HFILE_L_H
#define HFILE_L_H

typedef struct Item
{
    char *term;
    struct Item *next;
} Item;

typedef struct Stack
{
    Item *top;
} Stack;

void push(Stack *stack, char *elem);
char *pop(Stack *stack);
int size(Stack *stack);
void freeing(Stack* stack);
Stack* init();
int input(int *X);
char *readline(char *PROMPT);
char *process(char *src);

#endif