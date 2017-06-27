#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#define maxn 1000
#define maxlen 100
#define maxascii 128

//霍夫曼编码:一般是二叉树，编码为01串
//霍夫曼编码:一个字符的编码不能是另外一个编码的前缀，即不能产生歧义
//对于二叉树，因为一般翻译后的电文要尽量短，所以一般01编码不会很长
//对于最小的霍夫曼编码，叶子结点(信息)数目比内部结点(过程)数目大1，即有n个字符时，树结点数目为2n+1

//不能计算值，如00000和0是不一样的,不能都记为0
struct node
{
    char ch;
    struct node *left,*right;
}*tree;

struct rec
{
    long value;
    struct node *pos;
}a[maxn+1];

char code[maxascii][maxlen],str[maxlen];

void work1()
{
    long n,len,i,j,k;
    char c,s[30];
    struct node *pos,*p;
    tree=(struct node *) malloc (sizeof(struct node));
    tree->left=NULL;
    tree->right=NULL;
    printf("Please input n rule(s):\t");
    scanf("%ld",&n);
    printf("Please input char & coding\n");
    for (k=1;k<=n;k++)
    {
        //skip '\n'
        scanf("%c",&c);
        scanf("%c%s",&c,s);
        if (strcmp(s,"")==0)
        {
            system("cls");
            printf("Wrong\n");
            break;
        }
        strcpy(code[(long)c],s);
        len=strlen(s);
        pos=tree;
        for (i=0;i<len;i++)
            if (s[i]=='0')
            {
                if (pos->left==NULL)
                {
                    p=(struct node *) malloc (sizeof(struct node));
                    pos->left=p;
                    pos=p;
                    break;
                }
                else
                    pos=pos->left;
            }
            else
            {
                if (pos->right==NULL)
                {
                    p=(struct node *) malloc (sizeof(struct node));
                    pos->right=p;
                    pos=p;
                    break;
                }
                else
                    pos=pos->right;
            }
        //编码经过的结点都在树中，未新建结点，即这个编码必定是之前一个编码的前缀
        if (i==len)
        {
            system("cls");
            printf("Wrong\n");
            break;
        }
        //结点要新建，即从根结点到这个新建的结点之间的01编码不是之前编码的前缀
        else
        {
            for (j=i+1;j<len;j++)
                if (s[j]=='0')
                {
                    p=(struct node *) malloc (sizeof(struct node));
                    pos->left=p;
                    pos->right=NULL;
                    pos=p;
                }
                else
                {
                    p=(struct node *) malloc (sizeof(struct node));
                    pos->left=NULL;
                    pos->right=p;
                    pos=p;
                }
            pos->left=NULL;
            pos->right=NULL;
            pos->ch=c;
        }
    }
}

void work2()
{
    char s[1000],str[10000];
    long i,len;
    printf("Please input a string:\n");
    printf("\tA blank line means the end of input\n");
    strcpy(str,"");
    gets(s);
    while (1)
    {
        gets(s);
        len=strlen(s);
        if (len==0)
            break;
        strcat(str,s);
    }
    len=strlen(str);
    for (i=0;i<len;i++)
        //judge whether exist or not,初始化为"",若有该字符的编码，则会修改，不为""        if (strcmp(code[(long)str[i]],"")==0)
        if (strcmp(code[(long)str[i]],"")==0)
        {
            system("cls");
            printf("Wrong\n");
            return ;
        }
        else
	    printf("%s",code[(long)str[i]]);
    printf("\n");
}

void work3()
{
    struct node *p;
    char s[1000],str[10000];
    long i,len;
    printf("Please input a string:\n");
    printf("\tA blank line means the end of input\n");
    strcpy(str,"");
    gets(s);
    while (1)
    {
        gets(s);
        len=strlen(s);
        if (len==0)
            break;
        strcat(str,s);
    }
    len=strlen(str);
    p=(struct node *) malloc (sizeof(struct node));
    p=tree;
    for (i=0;i<len;i++)
    {
        if (str[i]=='0')
        {
            if (p->left==NULL)
            {
                system("cls");
                printf("Wrong");
                return ;
            }
            else
                p=p->left;
        }
        else
        {
            if (p->right==NULL)
            {
                system("cls");
                printf("Wrong");
                return ;
            }
            else
                p=p->right;
        }
        if (p->left==NULL && p->right==NULL)
        {
            printf("%c",p->ch);
            p=tree;
        }
    }
    //若最后还有剩余，则是错误的
    if (p!=tree)
    {
        system("cls");
        printf("Wrong\n");
        return ;
    }
    printf("\n");
}

void CodeCh(struct node *p,long lens)
{
    //叶子结点(信息)
    if (p->left==NULL && p->right==NULL)
    {
        str[lens]='\0';
        strcpy(code[(long)p->ch],str);
        return ;
    }
    str[lens]='0';
    CodeCh(p->left,lens+1);
    str[lens]='1';
    CodeCh(p->right,lens+1);
    lens--;
}

void work4()
{
    long n,ans=0,i,j,k;
    struct node *p;
    struct rec temp;
    char c,ch[maxn+1];
    printf("Please input n rule(s):\t");
    scanf("%ld",&n);
    printf("Please input char & coding\n");
    for (i=1;i<=n;i++)
    {
        p=(struct node *) malloc (sizeof(struct node));
        //skip '\n'
        scanf("%c",&c);
        scanf("%c%ld",&ch[i],&a[i].value);
        p->ch=ch[i];
        p->left=NULL;
        p->right=NULL;
        a[i].pos=p;
    }
    for (i=n;i>1;i--)
    {
        //sort a[1]~a[i]
        for (j=i;j>1;j--)
            for (k=1;k<j;k++)
                if (a[k].value>a[k+1].value)
                {
                    temp=a[k];
                    a[k]=a[k+1];
                    a[k+1]=temp;
                }
        //merge

        //树根结点指向左右子树
        p=(struct node *) malloc (sizeof(struct node));
        p->left=a[1].pos;
        p->right=a[2].pos;
        a[1].value+=a[2].value;
        a[1].pos=p;
        a[2]=a[i];  //last element , 填补空位
        ans+=a[1].value;
    }
    tree=a[1].pos;
    printf("Ans=%ld\n",ans);
    CodeCh(tree,0);
    for (i=1;i<=n;i++)
        printf("%c : %s\n",ch[i],code[(long)ch[i]]);
}

int main()
{
    //01串
    long mode,i;
    tree=(struct node *) malloc (sizeof(struct node));
    tree->left=NULL;
    tree->right=NULL;
    for (i=0;i<=maxascii;i++)
        strcpy(code[i],"");
    while (1)
    {
        system("cls");
        printf("0:exit\n");
        printf("1:Rule\n");
        printf("2:Coding\n");
        printf("3:Discoding\n");
/*给出所有字符出现的次数，对字符进行编码(只能是01)，使编码总长度最小
1.构建哈夫曼树；2.字符编码：从根结点开始到达字符所在的叶子结点，向左增加'0'.向右增加'1'*/
        printf("4:Build Rule\n");
        printf("Please input a mode:\t");
        scanf("%ld",&mode);
        switch(mode)
        {
            case 0:
                system("cls");
                exit(0);
            case 1:
                system("cls");
                printf("1:Rule\n");
                work1();
                break;
            case 2:
                system("cls");
                printf("2:Coding\n");
                work2();
                break;
            case 3:
                system("cls");
                printf("3:Discoding\n");
                work3();
                break;
            case 4:
                system("cls");
                printf("4:Build Rule\n");
                work4();
                break;
        }
        system("pause");
    }
    return 0;
}
/*
1
3
a 0
b 10
c 11

2
cbabc

2
abcd

3
111001011

3
01

4
8
a 10
b 20
c 15
d 32
e 40
f 60
g 26
h 18

*/
