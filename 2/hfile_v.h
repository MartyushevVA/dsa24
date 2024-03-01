#ifndef HFILE_V_H
#define HFILE_V_H

typedef struct Stack
{
    int top;
    char **list;
} Stack;

void push(Stack *stack, char *elem);
char *pop(Stack *stack);
int size(Stack *stack);
void freeing(Stack *stack);
Stack *init();
int input(int *X);
char *readline(char *PROMPT);
char *process(char *src);

#endif