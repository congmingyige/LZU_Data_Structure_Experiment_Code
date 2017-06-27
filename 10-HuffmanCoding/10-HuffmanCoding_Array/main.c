#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define maxs 1024
#define maxn 1000
#define maxlen 100
//��������Ϊ10��

//����������:һ���Ƕ�����������Ϊ01��
//����������:һ���ַ��ı��벻��������һ�������ǰ׺�������ܲ�������
//���ڶ���������Ϊһ�㷭���ĵ���Ҫ�����̣�����һ��01���벻��ܳ�
//������С�Ļ��������룬Ҷ�ӽ��(��Ϣ)��Ŀ���ڲ����(����)��Ŀ��1������n���ַ�ʱ���������ĿΪ2n+1

//ʹ�������¼��ֵ
//����ǰλֵΪ0��*2������ǰλֵΪ0��*2+1

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
    //�������ʣ�࣬���Ǵ����
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
    //Ҷ�ӽ��(��Ϣ)
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

        //�������ָ����������
        p=(struct node *) malloc (sizeof(struct node));
        p->left=a[1].pos;
        p->right=a[2].pos;
        a[1].value+=a[2].value;
        a[1].pos=p;
        a[2]=a[i];  //last element , ���λ
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
    //01��
    long mode,i;
    //һ���ַ��ı��벻��Ϊ��
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
