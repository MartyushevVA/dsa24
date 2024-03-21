#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "logic.h"

int dialog()
{
    char *msgs[] = {"0. Quit\n", "1. Add\n", "2. Find\n", "3. Delete\n", "4. Personal Task\n", "5. Show\n"};
    char *errmsg = "";
    int N = 6;
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

int D_Add(Table *ptab, Table *_)
{
    char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow"};
    int k, rc, n;
    char *info = NULL;
    printf("Enter key: ");
    n = input(&k);
    if (n)
        return 0;
    printf("Enter info: ");
    info = readline("");
    if (info == NULL)
        return 0;
    rc = L_Insert(ptab, (unsigned)k, info);
    free(info);
    printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}

int D_Find(Table *ptab, Table *_)
{
    int k, n;
    KeySpace *rc;
    char *info = NULL;
    printf("Enter key: ");
    n = input(&k);
    if (n)
        return 0;
    rc = L_Find(ptab, (unsigned)k);
    if (rc)
        printf("Key: %u | Info: %s\n", rc->key, rc->info);
    else
        printf("Doesn't exist\n");
    return 1;
}

int D_Delete(Table *ptab, Table *_)
{
    char *errmsgs[] = {"Ok", "Key wasn't found"};
    int k, rc, n;
    char *info = NULL;
    printf("Enter key: ");
    n = input(&k);
    if (n)
        return 0;
    rc = L_Delete(ptab, (unsigned)k);
    printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}

int D_Show(Table *ptab, Table *indiv)
{
    printf("Choose table: \n1. Main \n2. Additional \n");
    int k = 0;
    Table *matrs[] = {ptab, indiv};
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

int D_Personal_Task(Table *ptab, Table *indiv)
{
    unsigned int f, s;
    int n;
    char *info = NULL;
    printf("Enter first key: ");
    n = u_input(&f);
    if (n)
        return 0;
    printf("Enter second key: ");
    n = u_input(&s);
    if (n)
        return 0;
    n = L_PTask(ptab, indiv, (unsigned)f, (unsigned)s);
    if (n)
        L_Print(indiv);
    else
        printf("No valid keys\n");
    return 1;
}