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
//如果从最前的关键字开始到最后的关键字排序，则需要sort(p,q,w) data[x]~data[y]排第w个关键字，
    //然后延伸出sort(s,t,w+1) [p<=s<=t<=q]
//该方法耗费大量时间和内存，不推荐

struct node
{
    //关键字的值
    long key[g+1];
}data[maxn+1],f[maxn+1];
//next:下一个数的编号
//front,rear:一个链表的首,尾数据的编号

void sort(long p,long q,long w)
{
    long i,j,head,pos,value,next[maxn+1],front[y-x+1],rear[y-x+1],b[y+1],e[y+1];
    for (i=p;i<q;i++)
        next[i]=i+1;
    next[q]=0;
    head=p;
    //值为j的链表的首地址，0代表j链表没有元素
    for (j=x;j<=y;j++)
        front[j]=0;
    pos=head;
    ///分配
    while (pos)
    {
        //把一个数添加到value链表的末尾
        value=data[pos].key[w];
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
    for (i=p;i<=q;i++)
        f[i]=data[i];
    j=p-1;
    for (i=x;i<=y;i++)
        if (front[i]!=0)
        {
            b[i]=j+1;
            pos=front[i];
            while (pos!=rear[i])
            {
                j++;
                data[j]=f[pos];
                pos=next[pos];
            }
            j++;
            data[j]=f[pos];
            e[i]=j;
        }
    if (w!=g)
    {
        for (i=x;i<=y;i++)
            //没有数或者只有1个数就不用排了
            if (front[i]!=0 && b[i]!=e[i])
                sort(b[i],e[i],w+1);
    }
}

int main()
{
    long i,j,n;
    scanf("%ld",&n);
    for (i=1;i<=n;i++)
        for (j=1;j<=g;j++)
            scanf("%ld",&data[i].key[j]);
    sort(1,n,1);
    printf("\n");
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=g;j++)
            printf("%ld ",data[i].key[j]);
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
