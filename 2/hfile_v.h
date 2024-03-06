#ifndef HFILE_V_H
#define HFILE_V_H

typedef struct Stack
{
    int top;
    int allocated;
    char **list;
} Stack;

int check(Stack *stack);
void push(Stack *stack, char *elem);
char *pop(Stack *stack);
int size(Stack *stack);
void freeing(Stack *stack);
Stack *init(int allocated);
int input(int *X);
char *readline(char *PROMPT);
char *process(char *src, int allocated);

#endif