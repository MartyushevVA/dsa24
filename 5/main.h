#ifndef MAIN_H
#define MAIN_H
#include "lib.h"

int dialog();
int D_Add_Vert(Graph *);
int D_Add_Edge(Graph *);
int D_Delete_Vert(Graph *);
int D_Delete_Edge(Graph *);
int D_Change_Vert(Graph *);
int D_Print_List(Graph *);
int D_Print_Graph(Graph *);

int D_Passage(Graph*);
int D_Find_Min(Graph*);
int D_Special_Func(Graph*);

int D_Import(Graph *);
int D_Timing(Graph *);
int D_Extra_Task(Graph *);

#endif