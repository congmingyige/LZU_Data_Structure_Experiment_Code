#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct node
    {
        char c;
        struct node *pre,*next;
    };
    struct node *info,*temp;
    char ch;
    printf("Previous word :     ");

    info=(struct node *) malloc (sizeof(struct node));
    info=NULL;
    while ((ch=getchar())!='\n')
    {
        //������Ϊ��ʱ��temp->pre=NULL,info=temp,��ʱ��infoΪ������ָ��
        temp=(struct node *) malloc (sizeof(struct node));
        temp->c=ch;
        temp->pre=info;
        temp->next=NULL;
        if (info!=NULL)
            info->next=temp;
        info=temp;
    }
    printf("New word(Reverse) : ");
    while (info)
    {
        printf("%c",info->c);
        info=info->pre;
    }
    printf("\n");
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

