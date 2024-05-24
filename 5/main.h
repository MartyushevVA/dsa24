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

int D_Descendants(Graph*);
int D_Min_Dist(Graph*);
int D_Distribution(Graph*);

int D_Import(Graph *);

#endif