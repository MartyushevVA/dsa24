#ifndef MAIN_H
#define MAIN_H
#include "lib.h"

int input(int *);
int u_input(unsigned int *);
char *readline(char *);

int dialog();
int D_Add(Tree *);
int D_Delete(Tree *);
int D_Passage(Tree *);
int D_Find(Tree *);
int D_Special_Find(Tree *);
int D_Format_Print(Tree *);
int D_GraphViz_Print(Tree *);
int D_Import(Tree *);
int D_Timing(Tree *);

#endif