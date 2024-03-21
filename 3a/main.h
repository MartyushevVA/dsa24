#ifndef MAIN_H
#define MAIN_H
#include "lib.h"

int input(int *);
int u_input(unsigned int *);
char *readline(char *);
int dialog();
int D_Add(Table *, Table *);
int D_Find(Table *, Table *);
int D_Delete(Table *, Table *);
int D_Show(Table *, Table *);
int D_Personal_Task(Table *, Table *);

#endif