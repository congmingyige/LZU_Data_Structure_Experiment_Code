#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c,str[50];
    long len=0;
    FILE *fp=fopen("1.txt","r");
    while (fscanf(fp,"%c",&c)!=EOF)
    {
        if (!((c>='a' && c<='z') || (c>='A' && c<='Z') || (c=='-' && len!=0)))
            c=' ';
        if (c==' ')
        {
            if (len!=0)
            {
                str[len]='\0';
                printf("%s\n",str);
            }
        }
        else
        {
            str[len]=c;
            len++;
        }
    }
    return 0;
}
