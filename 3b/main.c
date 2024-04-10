#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main()
{
    int (*fptr[])(Table *) = {NULL, D_Add, D_Delete, D_Find, D_Show, D_Import, D_Export, D_Large_Finding, D_Refresh};
    int option, size;
    printf("Enter size of table: ");
    int n = input(&size);
    if (n)
        return 0;
    if (!size)
    {
        printf("Empty table\n");
        return 0;
    }
    Table *table = init(size);
    option = dialog();
    while (option)
    {
        if (!fptr[option](table))
            break;
        option = dialog();
    }
    printf("Done\n");
    clear(table);
    return 0;
}