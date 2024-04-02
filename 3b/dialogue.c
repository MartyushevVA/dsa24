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
    int rc;
    do
    {
        printf(errmsg);
        errmsg = "NOWAY\n";
        for (int i = 0; i < N; i++)
            printf(msgs[i]);
        printf("Choose: ");
        int n = input(&rc);
        if (n)
            rc = 0;
    } while (rc < 0 || rc >= N);
    return rc;
}

int D_Add(Table *ptab)
{
    char *errmsgs[] = {"Ok", "Similar hash | Extended", "Table overflow | Resized", "Extended + Resized"};
    unsigned int k, info;
    int rc, n;
    printf("Enter key: ");
    n = u_input(&k);
    if (n)
        return 0;
    printf("Enter info: ");
    n = u_input(&info);
    if (n)
        return 0;
    rc = L_Insert(ptab, k, info);
    printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}//

int D_Delete(Table *ptab)
{
    char *errmsgs[] = {"Ok", "Key wasn't found"};
    unsigned int k;
    int rc, n;
    printf("Enter key: ");
    n = u_input(&k);
    if (n)
        return 0;
    rc = L_Delete(ptab, k);
    printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}

int D_Find(Table *ptab)
{
    unsigned int k;
    int n;
    KeySpace *rc;
    printf("Enter key: ");
    n = u_input(&k);
    if (n)
        return 0;
    rc = L_Find(ptab, (unsigned)k);
    if (rc)
        printf("Key: %u | Info: %s\n", rc->key, rc->info);
    else
        printf("Doesn't exist\n");
    return 1;
}

int D_Show(Table *ptab)
{
    printf("Choose table: \n1. Main \n2. Additional \n");
    int k = 0;
    Table *matrs[] = {ptab};
    int n = input(&k);
    if (n)
        return 0;
    if (k < 1 || k > 2)
        return 1;
    int rc = L_Print(matrs[k - 1]);
    if (!rc)
        printf("Table is empty\n");
    return 1;
}

int D_Import(Table *ptab)
{
    char *errmsgs[] = {"Loaded", "File doesn't exist", "File empty", "Table overflow"};
    char *fname = NULL;
    int check = 0;
    int n;
    do
    {
        printf("Enter .txt file name: ");
        fname = readline("");
        if (fname == NULL)
            return 0;
        int size = (int)strlen(fname);
        if ((int)strlen(fname) > 3)
            check = (fname[size - 4] == '.' && fname[size - 3] == 't' && fname[size - 2] == 'x' && fname[size - 1] == 't');
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
        printf("Enter .txt file name: ");
        fname = readline("");
        if (fname == NULL)
            return 0;
        int size = (int)strlen(fname);
        if ((int)strlen(fname) > 3)
            check = (fname[size - 4] == '.' && fname[size - 3] == 't' && fname[size - 2] == 'x' && fname[size - 1] == 't');
    } while (!check);
    n = L_Export(ptab, fname);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Large_Finding(Table *ptab)
{

}

int D_Refresh(Table *ptab)
{

}