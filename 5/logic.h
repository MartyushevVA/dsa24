#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

int input(int *);
int u_input(unsigned int *);
char *readline(char *);

int L_Add_Vert(Graph*, char*, int, int, int);
int L_Add_Edge(Graph*, char*, char*);
int L_Delete_Vert(Graph*, char*);
int L_Delete_Edge(Graph*, char*, char*);
int L_Change_Vert(Graph*, char*, char*, int, int, int);

int L_Print_List(Graph*);
int L_Print_Graph(Graph*);

int L_Passage(Graph*, char*);
int L_Find_Min(Graph*, char*,char*);
int L_Special_Func(Graph*, char*, int);

int L_Import(Graph*, char*);
int L_Timing();
int L_Extra_Task(Graph*);

#endif