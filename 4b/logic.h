#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

int input(int *);
int u_input(unsigned int *);
char *readline(char *);
char **freadline(FILE *, int *);

int L_Add(Tree *, unsigned int, unsigned int);
int L_Delete(Tree *, unsigned int, int);
int L_Passage(Tree *, unsigned int *);
int L_Find(Tree *, unsigned int);
int L_Special_Find(Tree *, unsigned int);
void L_Format_Print(Tree *);
void L_GraphViz_Print(Tree *);
int L_Import(Tree *, char *);
int L_Timing();
int L_Add_Task(Tree *, char *, unsigned int);

#endif