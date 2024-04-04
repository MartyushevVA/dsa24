#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "logic.h"

int dialog()
{
    char *msgs[] = {"0. Quit\n", "1. Add\n", "2. Delete\n", "3. Find\n", "4. Show\n", "5. Import\n", "6. Export\n", "7. Finding\n", "8. Refresh\n"};
    char *errmsg = "";
    int N = 9;
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

int D_Add(Table *ptab)
{
    char *errmsgs[] = {"Ok", "Similar hash | Extended", "Table overflow | Resized", "Extended + Resized"};
    unsigned int k, info;
    int n;
    printf("Enter key: ");
    n = u_input(&k);
    if (n)
        return 0;
    printf("Enter info: ");
    n = u_input(&info);
    if (n)
        return 0;
    n = L_Insert(ptab, k, info);
    printf("%s: %d\n", errmsgs[n], k);
    return 1;
}

int D_Delete(Table *ptab)
{
    char *errmsgs[] = {"Ok", "Key wasn't found"};
    unsigned int k;
    int n;
    printf("Enter key: ");
    n = u_input(&k);
    if (n)
        return 0;
    n = L_Delete(ptab, k);
    printf("%s: %d\n", errmsgs[n], k);
    return 1;
}

int D_Find(Table *ptab)
{
    unsigned int k;
    int n;
    KeySpace *arr;
    int size = 0;
    printf("Enter key: ");
    n = u_input(&k);
    if (n)
        return 0;
    arr = L_Find(ptab, k, &size, 0);
    if (size)
        print_arr(arr, size);
    else
        printf("Doesn't exist\n");
    return 1;
}

int D_Show(Table *ptab)
{
    int n = L_Print(ptab);
    if (!n)
        printf("Table is empty\n");
    return 1;
}

int D_Import(Table *ptab)
{
    char *errmsgs[] = {"Loaded", "File doesn't exist", "File empty"};
    char *fname = NULL;
    int check = 0;
    int n;
    do
    {
        printf("Enter .bin file name: ");
        fname = readline("");
        if (fname == NULL)
            return 0;
        int size = (int)strlen(fname);
        if ((int)strlen(fname) > 3)
            check = (fname[size - 4] == '.' && fname[size - 3] == 'b' && fname[size - 2] == 'i' && fname[size - 1] == 'n');
    } while (!check);
    n = L_Import(ptab, fname);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Export(Table *ptab)
{
    char *errmsgs[] = {"Uploaded", "Nothing to export"};
    char *fname = NULL;
    int check = 0;
    int n;
    do
    {
        printf("Enter .bin file name: ");
        fname = readline("");
        if (fname == NULL)
            return 0;
        int size = (int)strlen(fname);
        if ((int)strlen(fname) > 3)
            check = (fname[size - 4] == '.' && fname[size - 3] == 'b' && fname[size - 2] == 'i' && fname[size - 1] == 'n');
    } while (!check);
    n = L_Export(ptab, fname);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Large_Finding(Table *ptab)
{
    unsigned int k;
    int n;
    KeySpace *arr;
    int size = 0;
    unsigned int release = 0;
    printf("Enter key: ");
    n = u_input(&k);
    if (n)
        return 0;
    printf("Enter release (0 if all versions): ");
    n = u_input(&release);
    if (n)
        return 0;
    arr = L_Find(ptab, k, &size, release);
    if (size)
        print_arr(arr, size);
    else
        printf("Doesn't exist\n");
    return 1;
}

int D_Refresh(Table *ptab)
{
    char *errmsgs[] = {"Refreshed", "Table is empty"};
    int n = L_Refresh(ptab);
    printf("%s\n", errmsgs[n]);
    return 1;
}