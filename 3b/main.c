#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "lib.h"

int main()
{
    int (*fptr[])(Table *) = {NULL, D_Add, D_Delete, D_Find, D_Show, D_Import, D_Export, D_Large_Finding, D_Refresh};
    int option, size;
    printf("Enter size of table: ");
    int n = input(&size);
    if (n)
        return 0;
    Table *table = init(size);
    while (option = dialog())
        if (!fptr[option](table))
            break;
    printf("Done\n");
    clear(table);
    return 0;
}