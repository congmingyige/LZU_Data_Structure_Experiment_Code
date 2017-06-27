#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main()
{
    struct node
    {
        char c;
        struct node *next;
    };
    struct node *info,*temp;
    char ch;
    printf("Previous word :     ");
    info=(struct node *) malloc (sizeof(struct node));
    info=NULL;
    while ((ch=getchar())!='\n')
    {
        temp=(struct node *) malloc (sizeof(struct node));
        temp->c=ch;
        temp->next=info;
        info=temp;
    }
    printf("New word(Reverse) : ");
    while (info)
    {
        temp=info;//
        printf("%c",info->c);
        info=info->next;
        free(temp);//
    }
    printf("\n");
    free(temp);//
    return 0;
}
/*
input:
1234
output:
4321
input:
1
output:
1
input:
blank
output:
blank
*/

