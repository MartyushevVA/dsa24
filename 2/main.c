#include <stdio.h>
#include <stdlib.h>
#include "hfile_v.h"
// #include "hfile_l.h"

int main()
{
    char *str;
    char *new;
    do
    {
        printf("Enter formula to transform:\n");
        str = readline("");
        if (!str)
        {
            printf("Done\n");
            return 0;
        }
        new = process(str);
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