#ifndef LOGIC_H
#define LOGIC_H
#include "lib.h"

int input(int *);
int u_input(unsigned int *);
char *readline(char *);

int L_Add_Vert(Graph *, char *, int, int, int);
int L_Add_Edge(Graph *, char *, char *);
int L_Delete_Vert(Graph *, char *);
int L_Delete_Edge(Graph *, char *, char *);
int L_Show_Vert(Graph *, char *);
int L_Change_Vert(Graph *, char *, char *, int, int, int);

int L_Print_List(Graph *);
int L_Print_Graph(Graph *);

int L_Descendants(Graph *, char *);
int L_Min_Dist(Graph *, char *, char *);
int L_Distribution(Graph *, char *, int);

int L_Import(Graph *, char *);

#endif