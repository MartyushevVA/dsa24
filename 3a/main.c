#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "lib.h"

int main()
{
    int (*fptr[])(Table *, Table *) = {NULL, D_Add, D_Find, D_Delete, D_Personal_Task, D_Show};
    int option, size;
    printf("Enter size of table: ");
    int n = input(&size);
    if (n)
        return 0;
    Table *table = init(size);
    Table *temporal = init(size);
    while (option = dialog())
    {
        if (!fptr[option](table, temporal))
            break;
    }
    printf("Done\n");
    clear(table);
    clear(temporal);
    return 0;
}