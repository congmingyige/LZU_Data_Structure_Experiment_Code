#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//Ӣ�ﵥ�ʰ�����'A'~'Z';'a'~'z';'-'    ��53������
/*
�ʱ�临�Ӷȣ�n words, m length , each character is different in corresponding position
��ôÿ�����ʵ�ÿ���ַ���Ҫ��ӵ���������
O(n*m*G) G=ʹ�õĲ�ͬ���ַ�������53����'a'~'z','A'~'Z','-'
*/

struct node
{
    struct node *value[53];
    //first position
    //initialization:count=0
    //if count=0 , set x,y value
    //if not , ignore it.
    long x,y,count;
}*tree,*pos,*p;
char ch[53],word[50];
long value[128],str[50],len,x,y;

void search(struct node *p,long l)
{
    long i;
    if (p->count!=0)
    {
        for (i=0;i<l;i++)
            printf("%c",word[i]);
        printf(" :\n");
        printf("count:\t%ld\n",p->count);
        printf("first occur:\t%ld %ld\n\n",p->x,p->y);
        //��ʱ�����˳�
    }
    for (i=0;i<53;i++)
        if (p->value[i]!=NULL)
        {
            word[l]=ch[i];
            search(p->value[i],l+1);
        }
}

void build()
{
    //posΪ��ǰ����ĩβ�����е�λ��
    long i,j;
    pos=(struct node *) malloc (sizeof(struct node));
    pos=tree;
    for (i=1;i<=len;i++)
        if (pos->value[str[i]]==NULL)
        {
            p=(struct node *) malloc (sizeof(struct node));
            pos->value[str[i]]=p;
            p->count=0;
            for (j=0;j<53;j++)
                p->value[j]=NULL;
            pos=p;
        }
        else
            pos=pos->value[str[i]];
    if (pos->count==0)
    {
        pos->x=x;
        pos->y=y-len;
    }
    pos->count++;

}

int main()
{
    char c,c_;
    long i;

    for (i=0;i<26;i++)
        ch[i]=(char)(i+65);
    for (i=26;i<52;i++)
        ch[i]=(char)(i+71);
    ch[52]='-';
    for (i=0;i<26;i++)
        value[i+65]=i;
    for (i=26;i<52;i++)
        value[i+71]=i;
    value[(long)'-']=52;

    tree=(struct node *) malloc (sizeof(struct node));
    tree->count=0;
    for (i=0;i<53;i++)
        tree->value[i]=NULL;

    //��һ���ַ�Ϊ��һ�У���һ��
    x=1;
    y=1;
    len=0;
    //��һ/����"Ctrl+Z"����(�ӻ�������)
    while (scanf("%c",&c)!=EOF)
    {
        c_=c;
        //character-processing
        //'-':newly-born
        if (!((c>='a' && c<='z') || (c>='A' && c<='Z') || (c=='-' && len!=0)))
            c=' ';
        if (c==' ')
        {
            if (len!=0)
            {
                build();
                len=0;
            }
        }
        else
        {
            len++;
            str[len]=value[(long)c];
        }

        if (c_=='\n')
        {
            x++;
            y=1;
        }
        else
            y++;
    }
    //�����ԣ��������ĵ���
    if (len!=0)
        build();
    search(tree,0);
    return 0;
}
