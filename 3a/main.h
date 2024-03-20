#ifndef MAIN_H
#define MAIN_H
#include "lib.h"

int input(int *);
char *readline(char *);
int dialog();
int D_Add(Table *, Table *);
int D_Find(Table *, Table *);
int D_Delete(Table *, Table *);
int D_Show(Table *, Table *);
int D_Show2(Table *, Table *);
int D_Personal_Task(Table *, Table *);

#endif