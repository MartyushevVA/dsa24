#ifndef MAIN_H
#define MAIN_H
#include "lib.h"

int input(int *);
int u_input(unsigned int *);
char *readline(char *);

int dialog();
int D_Add(Tree *);
int D_Delete(Tree *);
int D_Search(Tree *);
int D_Find(Tree *);
int D_SFind(Tree *);
int D_Tree_Print(Tree *);
int D_Graph(Tree *);
int D_Import(Tree *);

#endif