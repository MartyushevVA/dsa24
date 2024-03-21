#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

int L_Insert(Table *table, unsigned int key, char *info);
int L_Delete(Table *table, unsigned int key);
KeySpace *L_Find(Table *table, unsigned int key);
int L_Print(Table *table);
// int import(Table *table, /*файл*/);
int L_PTask(Table *table, Table *indiv, unsigned int begin, unsigned int end);

#endif