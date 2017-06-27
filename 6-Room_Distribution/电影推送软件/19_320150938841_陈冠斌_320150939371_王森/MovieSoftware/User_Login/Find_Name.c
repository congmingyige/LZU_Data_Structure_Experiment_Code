#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "E:\\MovieSoftware\\define.h"

int find_name(int UserAns,TCHAR *szUsername)
{
    int i;
    extern struct user user[1000];
    for (i=1;i<=UserAns;i++)
        if (strcmp(user[i].Name,szUsername)==0) return i;
    return 0;
}
