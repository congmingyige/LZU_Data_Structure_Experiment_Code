#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "E:\\MovieSoftware\\define.h"

void InitUser(long w)
{
    extern struct user user[1000];
    int i;
    //ֵΪ0����δ��
    user[w].Sex=0;
    user[w].Define=0;
    user[w].Age=0;
    user[w].Condition=0;
    for (i=1;i<=9;i++)
        user[w].Preference[i]=false;
}
