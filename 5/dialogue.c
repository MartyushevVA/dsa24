#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "logic.h"

int dialog()
{
    char *msgs[] = {"0. Quit\n", "1. Add vertex\n", "2. Add edge\n", "3. Delete vertex\n",
                    "4. Delete edge\n", "5. Change Vertex\n", "6. Print as list\n",
                    "7. Print as graph\n", "8. Descendants\n", "9. Min Distance\n", "10. Distribution\n",
                    "11. Import\n", "12. Timing\n", "13. Extra task\n"};
    char *errmsg = "";
    int N = 14;
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

int D_Add_Vert(Graph *graph)
{
    char *errmsgs[] = {"| Ok", "Already exist"};
    int n;
    int sex, born, died;
    printf("Enter name: ");
    char *name = readline("");
    if (!name)
        return 0;
    printf("Enter sex: ");
    n = input(&sex);
    if (n)
    {
        free(name);
        return 0;
    }
    printf("Enter year of birth: ");
    n = input(&born);
    if (n)
    {
        free(name);
        return 0;
    }
    printf("Enter year of death: ");
    n = input(&died);
    if (n)
    {
        free(name);
        return 0;
    }
    n = L_Add_Vert(graph, name, sex, born, died);
    free(name);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Add_Edge(Graph *graph)
{
    char *errmsgs[] = {"| Ok", "| Missing second person", "| Already connected"};
    int n;
    printf("Enter first name: ");
    char *name_1 = readline("");
    if (!name_1)
        return 0;
    printf("Enter second name: ");
    char *name_2 = readline("");
    if (!name_2)
    {
        free(name_1);
        return 0;
    }
    n = L_Add_Edge(graph, name_1, name_2);
    free(name_1);
    free(name_2);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Delete_Vert(Graph *graph)
{
    char *errmsgs[] = {"| Ok", "| Doesn't exist"};
    int n;
    printf("Enter name: ");
    char *name = readline("");
    if (!name)
        return 0;
    n = L_Delete_Vert(graph, name);
    free(name);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Delete_Edge(Graph *graph)
{
    char *errmsgs[] = {"| Ok", "| Missing second person", "| There is no connection"};
    int n;
    printf("Enter first name: ");
    char *name_1 = readline("");
    if (!name_1)
        return 0;
    printf("Enter second name: ");
    char *name_2 = readline("");
    if (!name_2)
    {
        free(name_1);
        return 0;
    }
    n = L_Delete_Edge(graph, name_1, name_2);
    free(name_1);
    free(name_2);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Change_Vert(Graph *graph)
{
    char *errmsgs[] = {"| Ok", "| Doesn't exist"};
    int n;
    int sex, born, died;
    printf("Enter existing name: ");
    char *name_x = readline("");
    if (!name_x)
        return 0;
    printf("Enter new name: ");
    char *name_n = readline("");
    if (!name_n)
    {
        free(name_x);
        return 0;
    }
    printf("Enter new sex: ");
    n = input(&sex);
    if (n)
    {
        free(name_x);
        free(name_n);
        return 0;
    }
    printf("Enter new year of birth: ");
    n = input(&born);
    if (n)
    {
        free(name_x);
        free(name_n);
        return 0;
    }
    printf("Enter new year of death: ");
    n = input(&died);
    if (n)
    {
        free(name_x);
        free(name_n);
        return 0;
    }
    n = L_Change_Vert(graph, name_x, name_n, sex, born, died);
    free(name_n);
    free(name_x);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Print_List(Graph *graph)
{
    L_Print_List(graph);
    return 1;
}
int D_Print_Graph(Graph *graph)
{
    L_Print_Graph(graph);
    return 1;
}

int D_Descendants(Graph *graph)
{
    char *errmsgs[] = {"| Ok", "| Doesn't exist"};
    int n;
    printf("Enter name: ");
    char *name = readline("");
    if (!name)
        return 0;
    n = L_Descendants(graph, name);
    free(name);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Min_Dist(Graph *graph)
{
    char *errmsgs[] = {"| Ok", "| Missing second person"};
    int n;
    printf("Enter first name: ");
    char *name_1 = readline("");
    if (!name_1)
        return 0;
    printf("Enter second name: ");
    char *name_2 = readline("");
    if (!name_2)
    {
        free(name_1);
        return 0;
    }
    n = L_Min_Dist(graph, name_1, name_2);
    free(name_1);
    free(name_2);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Distribution(Graph *graph)
{
    char *errmsgs[] = {"| Ok", "| Doesn't exist"};
    int n;
    int cash;
    printf("Enter name: ");
    char *name = readline("");
    if (!name)
        return 0;
    printf("Enter quantity of money: ");
    n = input(&cash);
    if (n)
    {
        free(name);
        return 0;
    }
    n = L_Distribution(graph, name, cash);
    free(name);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Import(Graph *graph)
{
    char *errmsgs[] = {"Loaded", "File doesn't exist", "File empty"};
    char *fname = NULL;
    int check = 0;
    int n;
    do
    {
        printf("Enter .txt file name: ");
        if (fname)
            free(fname);
        fname = readline("");
        if (!fname)
            return 0;
        int size = (int)strlen(fname);
        if ((int)strlen(fname) > 3)
            check = (fname[size - 4] == '.' && fname[size - 3] == 't' && fname[size - 2] == 'x' && fname[size - 1] == 't');
    } while (!check);
    n = L_Import(graph, fname);
    printf("%s\n", errmsgs[n]);
    return 1;
}

int D_Timing(Graph *graph)
{
    return L_Timing();
}

int D_Extra_Task(Graph *graph)
{
}