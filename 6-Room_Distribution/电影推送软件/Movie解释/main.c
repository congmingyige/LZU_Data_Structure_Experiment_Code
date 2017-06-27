#include <stdio.h>
#include <stdlib.h>

void init();

int main(int argc,char *argv[])
{
    char c,s[50]="",s1[50]="",s2[50]="";
    int i,j;
    j=0;
    for (i=0;*(argv[0]+i);i++)
    {
        s[j]=*(argv[0]+i);
        if (*(argv[0]+i)=='\\')
        {
            j++;
            s[j]='\\';
        }
        j++;
    }
    while (s[j]!='\\') j--;
    j-=2;
    while (s[j]!='\\') j--;
    j-=2;
    while (s[j]!='\\') j--;
    s[j+1]='\0';
    strcpy(s1,s);
    strcat(s1,"codeblocks-16.01mingw-setup");
    strcpy(s2,s);
    strcat(s2,"Thunder_dl_7.9.43.5054");

    printf("Welcome to use Movie Software\n");
    printf("Install codeblocks? Y/N\n");
    c=getchar();
    if (c=='N' || c=='n') system(s1);
    c=getchar();
    printf("Install Thunder? Y/N\n");
    c=getchar();
    if (c=='N' || c=='n') system(s2);

    return 0;
}
