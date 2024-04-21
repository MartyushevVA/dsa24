#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main()
{
    int (*fptr[])(Tree *) = {NULL, D_Add, D_Delete, D_Search, D_Find, D_SFind, D_Tree_Print, D_Graph, D_Import};
    int option;
    Tree *tree = init();
    option = dialog();
    while (option)
    {
        if (!fptr[option](tree))
            break;
        option = dialog();
    }
    printf("Done\n");
    clear(tree->root);
    free(tree);
    return 0;
}