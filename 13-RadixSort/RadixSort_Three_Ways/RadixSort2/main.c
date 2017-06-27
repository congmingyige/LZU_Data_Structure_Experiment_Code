#include <stdio.h>
#include <stdlib.h>
//个数
#define maxn 1000
//数的范围 x~y
#define x 0
#define y 9
//关键字个数
#define g 3

//n个数，每个数有g个关键字
//可以在一次基数排序(桶排序)后，结合其它排序
//适用于：2~3个关键字，第一个关键字的范围较大，且分布较为分散，
    //通过第一个关键字把数分成若干个区间后，区间的大小较小，从而每个区间的排序时间也较小

struct node
{
    //关键字的值
    long key[g+1];
}data[maxn+1],f[maxn+1];
//next:下一个数的编号
//front,rear:一个链表的首,尾数据的编号
long next[maxn+1],front[y-x+1],rear[y-x+1];

void qsort_(long l,long r)
{
    long i,j,p,q;
    struct node t;
    i=l; j=r; p=f[(l+r)>>1].key[2]; q=f[(l+r)>>1].key[3];
    while (i<=j)
    {
        while (f[i].key[2]<p || (f[i].key[2]==p && f[i].key[3]<q)) i++;
        while (f[j].key[2]>p || (f[j].key[2]==p && f[j].key[3]>q)) j--;
        if (i<=j)
        {
            t=f[i];
            f[i]=f[j];
            f[j]=t;
            i++;
            j--;
        }
    }
    if (i<r) qsort_(i,r);
    if (j>l) qsort_(l,j);
}

int main()
{
    long n,i,j,head,pos,value,b;
    scanf("%ld",&n);
    for (i=1;i<=n;i++)
        for (j=1;j<=g;j++)
            scanf("%ld",&data[i].key[j]);
    for (i=1;i<n;i++)
        next[i]=i+1;
    next[n]=0;
    head=1;
    ///key 1

    //值为j的链表的首地址，0代表j链表没有元素
    for (j=x;j<=y;j++)
        front[j]=0;
    pos=head;
    ///分配
    while (pos)
    {
        //把一个数添加到value链表的末尾
        value=data[pos].key[1];
        //如果原来value链表有元素，则原来value链表的末尾元素的后继为第pos个数
        //如果原来value链表没有元素，则value链表的起始元素为第pos个数
        if (front[value]!=0)
            next[rear[value]]=pos;
        else
            front[value]=pos;
        //当前value链表的末尾元素为第pos个数
        rear[value]=pos;
        pos=next[pos];
    }
    ///收集
    printf("\n");
    j=0;
    for (i=x;i<=y;i++)
        if (front[i]!=0)
        {
            b=j+1;
            pos=front[i];
            while (pos!=rear[i])
            {
                j++;
                f[j]=data[pos];
                pos=next[pos];
            }
            j++;
            f[j]=data[pos];
            qsort_(b,j);
        }
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=g;j++)
            printf("%ld ",f[i].key[j]);
        printf("\n");
    }
    return 0;
}
/*
input:
10
1 1 2
9 7 9
3 8 5
1 3 3
5 4 3
6 8 5
2 1 3
1 4 5
9 1 1
5 1 3
output:
1 1 2
1 3 3
1 4 5
2 1 3
3 8 5
5 1 3
5 4 3
6 8 5
9 1 1
9 7 9
*/

