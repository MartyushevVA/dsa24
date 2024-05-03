#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

int L_Add(Tree *, unsigned int, unsigned int);
int L_Delete(Tree *, unsigned int, int);
int L_Search(Tree *, unsigned int, unsigned int);
int L_Find(Tree *, unsigned int);
int L_Special_Find(Tree *, unsigned int);
void L_Format_Print(Tree *);
void L_GraphViz_Print(Tree *);
int L_Import(Tree *, char *);
int L_Timing();

#endif