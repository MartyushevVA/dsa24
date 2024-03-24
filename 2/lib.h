#ifndef LIB_H
#define LIB_H

typedef struct Stack Stack;

int check(Stack *stack);
void push(Stack *stack, char *elem);
char *pop(Stack *stack);
int size(Stack *stack);
void freeing(Stack *stack);
Stack *init(int allocated);

#endif