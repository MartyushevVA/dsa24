#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

int L_Insert(Table *, unsigned int, unsigned int);
int L_Delete(Table *, unsigned int);
KeySpace *L_Find(Table *, unsigned int, int *);
int L_Print(Table *);
void print(KeySpace *, int);

#endif