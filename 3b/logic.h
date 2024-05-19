#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

int L_Insert(Table *, unsigned int, unsigned int);
int L_Delete(Table *, unsigned int);
int L_Find(Table *, unsigned int, int);
int L_Print(Table *);
int L_Import(Table *, char *);
int L_Export(Table *, char *);
int L_Refresh(Table *);

#endif