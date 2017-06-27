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

struct node
{
    char ch;
    struct node *left,*right;
}*tree[maxn+1];

struct rec
{
    long value,addr;
}a[maxn+1];

char code[maxascii][maxlen],str[maxlen];
long root;

//对已有编码建树：每增加一个0/1，若没有边，则编号加1，建结点;否则到达对应编号的结点
//越距离根结点，编号最小，根结点编号为1

//设计字符编码：建树：每次添加一个结点，结点编号加1，建结点，连接已有的两棵子树
//越距离根结点，编号最大，根结点编号为2*n-1(编号最大)

//对于已有边牧建树不需要静态链表，而设计字符编码需要字符编码，否则较复杂
//使用正常链表：同时结构体添加指针变量？？？

void work1()
{
    long n,len,sum,i,j,k;
    char c,s[maxlen];
    struct node *pos;
    tree[1]=(struct node *) malloc (sizeof(long));
    tree[1]->left=NULL;
    tree[1]->right=NULL;
    sum=1;
    root=1;

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
        pos=tree[1];
        for (i=0;i<len;i++)
            if (s[i]=='0')
            {
                if (pos->left==NULL)
                {
                    sum++;
                    tree[sum]=(struct node *) malloc (sizeof(struct node));
                    pos->left=tree[sum];
                    pos=tree[sum];
                    break;
                }
                else
                    pos=pos->left;
            }
            else
            {
                if (pos->right==NULL)
                {
                    sum++;
                    tree[sum]=(struct node *) malloc (sizeof(struct node));
                    pos->right=tree[sum];
                    pos=tree[sum];
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
                    sum++;
                    tree[sum]=(struct node *) malloc (sizeof(struct node));
                    pos->left=tree[sum];
                    pos->right=NULL;
                    pos=tree[sum];
                }
                else
                {
                    sum++;
                    tree[sum]=(struct node *) malloc (sizeof(struct node));
                    pos->right=tree[sum];
                    pos->right=NULL;
                    pos=tree[sum];
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
        //judge whether exist or not,初始化为"",若有该字符的编码，则会修改，不为""
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
    p=tree[root];

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
            p=tree[root];
        }
    }
    //若最后还有剩余，则是错误的
    if (p!=tree[root])
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
}

void work4()
{
    long n,ans=0,num,i,j,k;
    struct rec temp;
    char c;
    printf("Please input n rule(s):\t");
    scanf("%ld",&n);
    printf("Please input char & coding\n");
    for (i=1;i<=n;i++)
    {
        //skip '\n'
        scanf("%c",&c);
        tree[i]=(struct node *) malloc (sizeof(struct node));
        scanf("%c %ld",&tree[i]->ch,&a[i].value);
        a[i].addr=i;
        tree[i]->left=NULL;
        tree[i]->right=NULL;
    }
    num=n;
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
        num++;
        tree[num]=(struct node *) malloc (sizeof(struct node));
        a[1].value+=a[2].value;
        tree[num]->left=tree[a[1].addr];
        tree[num]->right=tree[a[2].addr];
        a[1].addr=num;          //new point number
        a[2].value=a[i].value;    //fill the blank
        a[2].addr=a[i].addr;
        ans+=a[1].value;
    }
    root=num;

    printf("Ans=%ld\n",ans);
    //根结点的编号
    CodeCh(tree[root],0);
    for (i=1;i<=n;i++)
        printf("%c : %s\n",tree[i]->ch,code[(long)tree[i]->ch]);

}

int main()
{
    long mode,i;
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
