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
//排序：从最后的关键字开始到最前的关键字
//分配+收集
//每个关键字分配+收集需要n+n时间，而共有g个关键字，时间复杂度为O(2ng)，效率很高。
//如果用数组，数据集中在一个区间，则区间的长度很长，另外的区间的内存浪费了。
//用链表可以解决这个问题，且数据不需要先后顺序，所以无必要非要用数组

struct node
{
    //关键字的值
    long key[g+1];
}data[maxn+1];
//next:下一个数的编号
//front,rear:一个链表的首,尾数据的编号
long next[maxn+1],front[y-x+1],rear[y-x+1];

int main()
{
    long n,i,j,head,pos,value,t;
    scanf("%ld",&n);
    for (i=1;i<=n;i++)
        for (j=1;j<=g;j++)
            scanf("%ld",&data[i].key[j]);
    for (i=1;i<n;i++)
        next[i]=i+1;
    next[n]=0;
    head=1;
    //key i
    for (i=g;i>=1;i--)
    {
        //值为j的链表的首地址，0代表j链表没有元素
        for (j=x;j<=y;j++)
            front[j]=0;
        pos=head;
        ///分配
        while (pos)
        {
            //把一个数添加到value链表的末尾
            value=data[pos].key[i];
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
        //把x链表,x+1链表,……,y链表 连接起来，而k链表的最后一个元素的后继为k+1链表的第一个元素
        value=x;
        while (front[value]==0)
            value++;
        head=front[value];
        while (value<=y)
        {
            t=value+1;
            while (front[t]==0 && t<=y)
                t++;
            if (t==y+1)
                break;
            next[rear[value]]=front[t];
            value=t;
        }
        next[rear[value]]=0;
    }
    printf("\n");
    pos=head;
    while (pos)
    {
        for (i=1;i<=g;i++)
            printf("%ld ",data[pos].key[i]);
        printf("\n");
        pos=next[pos];
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
