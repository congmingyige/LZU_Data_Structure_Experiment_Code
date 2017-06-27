#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//链表形式进行存储
struct node
{
    double value;
    long w;
    struct node *next;
};
long mode;
bool vis=false;

//x为存储位置
void input_op(struct node **x)
{
    struct node *y;
    char s[100],t[100];
    long len,i,j,sym=1;
    bool vis1;
    scanf("%s",s);
    if (s[0]!='-')
    {
        strcpy(t,"+");
        strcat(t,s);
        strcpy(s,t);
    }
    len=strlen(s);
    i=0;
    //A=3.5*x^5+2*x^4-3x^3+x
    //B=3.5x^4-x+1.5x^2+3
    while (i<len)
    {
        y=(struct node *) malloc (sizeof(struct node));
        if (s[i]=='+')
            sym=1;
        else
            sym=-1;
        i++;
        j=i;
        while (s[i]!='*' && s[i]!='x' && s[i]!='+' && s[i]!='-' && s[i]!='\0')
            i++;
        if (i!=j)
        {
            strncpy(t,s+j,i-j);
            t[i-j]='\0';
            y->value=atof(t)*sym;
        }
        else
            y->value=1.0*sym;
        if (s[i]=='*')
            i++;
        if (s[i]=='x')
        {
            i++;
            vis1=true;
        }
        else
            vis1=false;

        if (s[i]=='^')
            i++;
        j=i;
        while (s[i]!='+' && s[i]!='-' && s[i]!='\0')
            i++;
        if (i==j && !vis1)
            y->w=0;
        else if (i==j && vis1)
            y->w=1;
        else
        {
            strncpy(t,s+j,i-j);
            t[i-j]='\0';
            y->w=atoi(t);
        }
        y->next=(*x);
        (*x)=y;
    }
}

//x为要进行排序的链表
void sort_link(struct node **x)
{
    //交换排序(for i=1 to n-1 do ; for j=i+1 to n do if(a[i]>a[j]) then {t=a[i]; a[i]=a[j]; a[j]=t;})
    struct node *b=*x,*t;
    double d;
    long l;
    while (b)
    {
        t=b->next;
        while (t)
        {
            if (b->w < t->w)
            {
                l=b->w;
                b->w=t->w;
                t->w=l;
                d=b->value;
                b->value=t->value;
                t->value=d;
            }
            t=t->next;
        }
        b=b->next;
    }
}

void print(double u,long v)
{
    //0 no output
    if (u!=0)
    {
        //如果没有输出过，"+"号要省略
        if (u>0 && vis)
            printf("+");
        //-1 ignore 1
        if (fabs(u+1.0)<0.0000000001)
            printf("-");
        //1 ignore 1
        else if (!fabs(u-1.0)<0.0000000001)
            printf("%lf",u);
        if (v==1)
            printf("x");
        else if (v!=0)
            printf("x^%ld",v);
        vis=true;
    }
}

int main()
{
    struct node *a,*b,*x,*y;
    //etc. 3.5*x^5+2*x^4-3x^3+x
    //1.一元多项式的定义中没有x^-1(负数)等的情况
    //2.未知变量为x
    //3.不一定按照次数从高到低或从低到高的顺序
    //4.有可能省略乘号
    //5.系数可为实数
    //6.次数相同的项有可能出现多次
    //7.有可能最高项系数为0，输入0
    a=(struct node *) malloc (sizeof(struct node));
    b=(struct node *) malloc (sizeof(struct node));
    a=NULL;
    b=NULL;
    ///input
    //A
    printf("A= ");
    /*或者x=a;
    input_op()子函数直接用x*/
    input_op(&a);
    //B
    printf("B= ");
    input_op(&b);
    ///sort
    //A
    sort_link(&a);
    //B
    sort_link(&b);
    ///plus=0 or minus=1
    printf("plus=0 or minus=1 : ");
    scanf("%ld",&mode);
    x=a;
    y=b;
    //最高位，特殊情况————如果是正数不用写
    //a(x=a),b(y=b)没有为空的情况
    //结果从最高位到最低位输出
    while (x && y)
    {
        //合并次数相同的情况
        while (x->next && x->w==x->next->w)
        {
            x->next->value+=x->value;
            x=x->next;
        }
        while (y->next && y->w==y->next->w)
        {
            y->next->value+=y->value;
            y=y->next;
        }
        if (x->w > y->w)
        {
            print(x->value,x->w);
            x=x->next;
        }
        else if (x->w < y->w)
        {
            if (mode==0)
                print(y->value,y->w);
            else
                print(-y->value,y->w);
            y=y->next;
        }
        else
        {
            if (mode==0)
                print(x->value+y->value,x->w);
            else
                print(x->value-y->value,x->w);
            x=x->next;
            y=y->next;
        }
    }
    while (x)
    {
        print(x->value,x->w);
        x=x->next;
    }
    while (y)
    {
        print(y->value,y->w);
        y=y->next;
    }
    //次数大于0的项的系数全为0，输出0
    if (!vis)
        printf("0");
    printf("\n");
    return 0;
}
/*
0
x
0

0
x
1
*/
/*
-x+5
-x^2+x
1
*/
