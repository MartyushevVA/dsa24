#ifndef HFILE_H
#define HFILE_H

typedef struct
{
    int width;
    int *line;
} Row;

typedef struct
{
    int hight;
    Row *list;
} Matr;

int dig(int a);
int check(int X, int size, int *mas);
int input(int *X);
char *readline(char *PROMPT);
int *row(int *size);
int minput(Matr *matr, int i);
void process(Matr *new, int i, Matr *matr);
void freeing(Matr *matr, int size);

#endif