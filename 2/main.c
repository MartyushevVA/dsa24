#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "funcs.h"

int main()
{
    char *str;
    char *new;
    int allocated;
    printf("Enter size of stack (only vector): ");
    if (input(&allocated))
    {
        printf("End\n");
        return 0;
    }
    do
    {
        printf("Enter formula to transform:\n");
        str = readline("");
        if (!str)
        {
            printf("Done\n");
            return 0;
        }
        new = process(str, allocated);
        free(str);
        if (!new)
            printf("Wrong format\n");
        else
        {
            printf("%s\n", new);
            free(new);
        }
    } while (1);
    printf("End\n");
    return 0;
}