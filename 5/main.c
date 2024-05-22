#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main()
{
    int (*fptr[])(Graph *) = {NULL, D_Add_Vert, D_Add_Edge, D_Delete_Vert, D_Delete_Edge, D_Change_Vert, D_Print_List, D_Print_Graph, D_Descendants, D_Min_Dist, D_Distribution, D_Import, D_Timing, D_Extra_Task};
    int option;
    Graph *graph = init_graph();
    option = dialog();
    while (option)
    {
        if (!fptr[option](graph))
            break;
        option = dialog();
    }
    printf("Done\n");
    remove_graph(graph);
    return 0;
}