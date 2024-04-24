#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

int L_Add(Tree *, char *, unsigned int);
int L_Delete(Tree *, char *);
int L_Search(Tree *, char *, char *);
int L_Find(Tree *, char *);
int L_Special_Find(Tree *, char *);
void L_Format_Print(Tree *);
void L_GraphViz_Print(Tree *);
int L_Import(Tree *, char *);

#endif