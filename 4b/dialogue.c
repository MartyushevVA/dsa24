#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "logic.h"

int dialog()
{
    char *msgs[] = {"0. Quit\n", "1. Add\n", "2. Delete\n", "3. Passage (LRR)\n", "4. Search\n", "5. Special search\n", "6. Format print\n", "7. GraphViz print\n", "8. Import\n", "9. Timing\n"};
    char *errmsg = "";
    int N = 10;
    int choice = 0;
    do
    {
        printf(errmsg);
        errmsg = "NOWAY\n";
        for (int i = 0; i < N; i++)
            printf(msgs[i]);
        printf("Choose: ");
        int n = input(&choice);
        if (n)
            choice = 0;
    } while (choice < 0 || choice >= N);
    return choice;
}

int D_Add(Tree *tree)
{
    char *errmsgs[] = {"| Ok", "| Same key exist"};
    unsigned int key, info;
    int n;
    printf("Enter key: ");
    n = u_input(&key);
    if (n)
        return 0;
    printf("Enter info: ");
    n = u_input(&info);
    if (n)
        return 0;
    n = L_Add(tree, key, info);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Delete(Tree *tree)
{
    char *errmsgs[] = {"| Ok", "| Key wasn't found", "| One of inner elems was deleted"};
    unsigned int key;
    int n, pos;
    printf("Enter key: ");
    n = u_input(&key);
    if (n)
        return 0;
    printf("Enter position: ");
    n = input(&pos);
    if (n)
        return 0;
    n = L_Delete(tree, key, pos);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Passage(Tree *tree)
{
    char *errmsgs[] = {"| Ok", "| Nothing"};
    int n;
    unsigned int *border = (unsigned int *)malloc(2 * sizeof(unsigned int));
    printf("Enter first key: ");
    n = u_input(border);
    if (n)
        return 0;
    printf("Enter second key: ");
    n = u_input(&(border[1]));
    if (n)
        return 0;
    n = L_Passage(tree, border);
    printf("%s\n", errmsgs[n]);
    free(border);
    return 1;
}

int D_Find(Tree *tree)
{
    char *errmsgs[] = {"| Ok", "| Key wasn't found"};
    int n;
    unsigned int key;
    printf("Enter key: ");
    n = u_input(&key);
    if (n)
        return 0;
    n = L_Find(tree, key);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Special_Find(Tree *tree)
{
    char *errmsgs[] = {"| Ok", "| Key wasn't found"};
    int n;
    unsigned int key;
    printf("Enter key: ");
    n = u_input(&key);
    if (n)
        return 0;
    n = L_Special_Find(tree, key);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Format_Print(Tree *tree)
{
    L_Format_Print(tree);
    return 1;
}

int D_GraphViz_Print(Tree *tree)
{
    L_GraphViz_Print(tree);
    return 1;
}

int D_Import(Tree *tree)
{
    char *errmsgs[] = {"Loaded", "File doesn't exist", "File empty"};
    char *fname = NULL;
    int check = 0;
    int n;
    do
    {
        printf("Enter .txt file name: ");
        fname = readline("");
        if (!fname)
            return 0;
        int size = (int)strlen(fname);
        if ((int)strlen(fname) > 3)
            check = (fname[size - 4] == '.' && fname[size - 3] == 't' && fname[size - 2] == 'x' && fname[size - 1] == 't');
    } while (!check);
    n = L_Import(tree, fname);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Timing(Tree *tree)
{
    return L_Timing();
}