#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

int L_Insert(Table *, unsigned int, char *);
int L_Delete(Table *, unsigned int);
KeySpace *L_Find(Table *, unsigned int);
int L_Print(Table *);
int L_PTask(Table *, Table *, unsigned int, unsigned int);
int L_Import(Table *, char *);
int L_Export(Table *, char *);

#endif