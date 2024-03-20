#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "lib.h"

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

int D_Add(Table *ptab)
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
    rc = insert(ptab, (unsigned)k, info);
    free(info);
    printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}

int D_Find(Table *ptab)
{
    int k, n;
    KeySpace *rc;
    char *info = NULL;
    printf("Enter key: ");
    n = input(&k);
    if (n)
        return 0;
    rc = find(ptab, (unsigned)k);
    if (rc)
        printf("Key: %u | Info: %s\n", rc->key, rc->info);
    else
        printf("Doesn't exist\n");
    return 1;
}

int D_Delete(Table *ptab)
{
    char *errmsgs[] = {"Ok", "Key wasn't found"};
    int k, rc, n;
    char *info = NULL;
    printf("Enter key: ");
    n = input(&k);
    if (n)
        return 0;
    rc = delete (ptab, (unsigned)k);
    printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}

int D_Show(Table *ptab)
{
    print(ptab);
}

int D_Personal_Task(Table *ptab)
{
    int f, s, n;
    Table *rc;
    char *info = NULL;
    printf("Enter first key: ");
    n = input(&f);
    if (n)
        return 0;
    printf("Enter second key: ");
    n = input(&s);
    if (n)
        return 0;
    rc = pfind(ptab, (unsigned)f, (unsigned)s);
    print(rc);
    deleting(rc);
    return 1;
}