#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define maxs 1024
#define maxn 1000
#define maxlen 100
//树最多深度为10层

//霍夫曼编码:一般是二叉树，编码为01串
//霍夫曼编码:一个字符的编码不能是另外一个编码的前缀，即不能产生歧义
//对于二叉树，因为一般翻译后的电文要尽量短，所以一般01编码不会很长
//对于最小的霍夫曼编码，叶子结点(信息)数目比内部结点(过程)数目大1，即有n个字符时，树结点数目为2n+1

//使用数组记录数值
//若当前位值为0，*2；若当前位值为0，*2+1

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

long value[maxs];
bool use[maxs];
char code[128][30],str[maxlen];

void work1()
{
    long i,j,n,len,pos;
    char c,s[10];
    printf("Please input n rule(s):\t");
    scanf("%ld",&n);
    printf("Please input char & coding\n");
    for (j=1;j<=n;j++)
    {
        //skip '\n'
        scanf("%c",&c);
        scanf("%c%s",&c,s);
        strcpy(code[(long)c],s);
        len=strlen(s);
        pos=1;
        for (i=0;i<len;i++)
        {
            use[pos]=true;
            pos=pos<<1;
            if (s[i]=='1')
                pos++;
        }

        if (use[pos])
        {
            system("cls");
            printf("Wrong\n");
            break;
        }
        else
        {
            value[pos]=(long)c;
            strcpy(code[(long)c],s);
            use[pos]=true;
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
        if (strcmp(code[(long)str[i]],"")==0)
        {
            system("cls");
            printf("Wrong\n");
            break;
        }
        else
            printf("%s",code[(long)str[i]]);
    printf("\n");
}

void work3()
{
    char s[1000],str[10000];
    long i,len,pos;
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
    pos=1;
    for (i=0;i<len;i++)
    {
        if (str[i]=='0')
            pos=pos<<1;
        else
            pos=(pos<<1)+1;
        if (use[pos]==false)
        {
            system("cls");
            printf("Wrong\n");
            return ;
        }
        if (value[pos]!=-1)
        {
            printf("%c",(char)value[pos]);
            pos=1;
        }
    }
    //若最后还有剩余，则是错误的
    if (pos!=1)
    {
        system("cls");
        printf("Wrong\n");
        return ;
    }
    printf("\n");
}

void CodeCh(struct node *p,long lens,long chv)
{
    //叶子结点(信息)
    if (p->left==NULL && p->right==NULL)
    {
        str[lens]='\0';
        strcpy(code[(long)p->ch],str);
        value[chv]=(long)p->ch;
        return ;
    }
    str[lens]='0';
    CodeCh(p->left,lens+1,chv*2);
    str[lens]='1';
    CodeCh(p->right,lens+1,chv*2+1);
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
    CodeCh(tree,0,0);
    for (i=1;i<=n;i++)
        printf("%c : %s\n",ch[i],code[(long)ch[i]]);
}

int main()
{
    //01串
    long mode,i;
    //一个字符的编码不能为空
    for (i=1;i<maxs;i++)
    {
        use[i]=false;
        value[i]=-1;
    }
    for (i=0;i<128;i++)
        strcpy(code[i],"");
    while (1)
    {
        system("cls");
        printf("0:exit\n");
        printf("1:Rule\n");
        printf("2:Coding\n");
        printf("3:Discoding\n");
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
