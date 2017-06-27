#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
/*
int main(int argc,char *argv[])
{
    printf("%s",argv[0]);
}
*/

int main()
{
    char s[100];
    GetModuleFileName(NULL,s,100);
    printf("%s",s);
    return 0;
}
