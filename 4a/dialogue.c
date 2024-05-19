#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "logic.h"

int dialog()
{
    char *msgs[] = {"0. Quit\n", "1. Add\n", "2. Delete\n", "3. Search\n", "4. Find\n", "5. Special find\n", "6. Format print\n", "7. GraphViz print\n", "8. Import\n", "9. Timing\n"};
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
    int n;
    printf("Enter key: ");
    char *key = readline("");
    if (!key)
        return 0;
    printf("Enter info: ");
    unsigned int info;
    n = u_input(&info);
    if (n)
        return 0;
    n = L_Add(tree, key, info);
    free(key);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Delete(Tree *tree)
{
    char *errmsgs[] = {"| Ok", "| Key wasn't found"};
    int n;
    printf("Enter key: ");
    char *key = readline("");
    if (!key)
        return 0;
    n = L_Delete(tree, key);
    free(key);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Search(Tree *tree)
{
    int n;
    printf("Enter first key: ");
    char *key_1 = readline("");
    if (!key_1)
        return 0;
    printf("Enter second key: ");
    char *key_2 = readline("");
    if (!key_2)
    {
        free(key_1);
        return 0;
    }
    n = L_Search(tree, key_1, key_2);
    free(key_1);
    free(key_2);
    if (!n)
        printf("Nothing\n");
    return 1;
}

int D_Find(Tree *tree)
{
    int n;
    printf("Enter key: ");
    char *key = readline("");
    if (!key)
        return 0;
    n = L_Find(tree, key);
    free(key);
    if (!n)
        printf("Nothing\n");
    return 1;
}

int D_Special_Find(Tree *tree)
{
    int n;
    printf("Enter key: ");
    char *key = readline("");
    if (!key)
        return 0;
    n = L_Special_Find(tree, key);
    free(key);
    if (!n)
        printf("Nothing\n");
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

int D_Timing(Tree* tree)
{
    return L_Timing();
}