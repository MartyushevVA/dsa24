#ifndef MAIN_H
#define MAIN_H
#include "lib.h"

int input(int *);
int u_input(unsigned int *);
char *readline(char *);
int dialog();
int D_Add(Table *);
int D_Delete(Table *);
int D_Find(Table *);
int D_Show(Table *);
int D_Import(Table *);
int D_Export(Table *);
int D_Large_Finding(Table *);
int D_Refresh(Table *);

#endif