#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define maxn 1000

struct node
{
    long left,right;
}t[maxn+1];
long maxh=0,root;

//前序遍历
void DLR(long p)
{
    printf("%ld ",p);
    if (t[p].left!=0)
        DLR(t[p].left);
    if (t[p].right!=0)
        DLR(t[p].right);
}

//中序遍历
void LDR(long p)
{
    if (t[p].left!=0)
        LDR(t[p].left);
    printf("%ld ",p);
    if (t[p].right!=0)
        LDR(t[p].right);
}

//后序遍历
void LRD(long p)
{
    if (t[p].left!=0)
        LRD(t[p].left);
    if (t[p].right!=0)
        LRD(t[p].right);
    printf("%ld ",p);
}

/*
汇编：
子函数
call
ret

用静态链表
1.a 1.b 2.a 2.b …… 大小都是1个字节
注意push,pop 固定长度2个字节
*/

void DLR_NonRecursion(long p)
{
    if (p==0)
    {
        printf("Empty Tree\n");
        return ;
    }
    long stack[maxn+1],count=0,i;
    bool vis[maxn];
    //这里maxn可以改为n
    //false代表不在栈，true代表在栈
    for (i=1;i<=maxn;i++)
        vis[i]=false;
    while (p!=0 || count!=0)
    {
        while (p!=0)
        {
            printf("%ld ",p);
            //p不在栈中
            if (vis[p]==false)
            {
                //访问左节点
                p=t[p].left;
                if (p!=0)
                {
                    count=count+1;
                    stack[count]=p;
                    vis[p]=true;
                }
            }
            //p的左右子树还未完全遍历(这里指的是右子树)
            else if (t[p].right!=0 && vis[t[p].right])
            {
                p=t[p].right;
                count=count+1;
                stack[count]=p;
                vis[p]=true;
            }
        }
        //这里p=0，即前面的遍历完毕，这时需要出栈，获取节点
        if (count>0)
        {
            p=stack[count];
            count=count-1;
        }
    }
}

//void DLR_NonRecursion(long p)
//{
//    if (p==0)
//    {
//        printf("Empty Tree\n");
//        return ;
//    }
//    long stack[maxn+1],count=0;
//    while (p!=0 || count!=0)
//    {
//        while (p!=0)
//        {
//            count++;
//            stack[count]=p;
//            //输出父节点
//            printf("%ld ",p);
//            //遍历左子节点
//            p=t[p].left;
//        }
//        p=stack[count];
//        count--;
//        p=t[p].right;
//    }
//}

void LDR_NonRecursion(long p)
{
    if (p==0)
    {
        printf("Empty Tree\n");
        return ;
    }
    long stack[maxn+1],count=0;
    while (p!=0 || count!=0)
    {
        while (p!=0)
        {
            count++;
            stack[count]=p;
            //遍历左子节点
            p=t[p].left;
        }
        p=stack[count];
        count--;
        //输出父节点
        printf("%ld ",p);
        //遍历右子节点
        p=t[p].right;
    }
}

void LRD_NonRecursion(long p)
{
    if (p==0)
    {
        printf("Empty Tree\n");
        return ;
    }
    long stack[maxn+1],count=0,flag[maxn+1];
    while (p!=0)
    {
        count++;
        stack[count]=p;
        flag[count]=0;
        p=t[p].left;
    }
    while (count!=0)
    {
        p=stack[count];
        while (t[p].right!=0 && flag[count]==0)
        {
            flag[count]=1;
            p=t[p].right;
            while (p)
            {
                count++;
                stack[count]=p;
                flag[count]=0;
                p=t[p].left;
            }
        }
        p=stack[count];
        printf("%ld ",p);
        count--;
    }
}

void ChangeSubtree(long p)
{
    long temp;
    temp=t[p].left;
    t[p].left=t[p].right;
    t[p].right=temp;
}

//统计高度
//或者建树(遍历)时对每一个点处理,height[t[p].left/right]=height[p]+1
void count(long p,long h)
{
    if (p==0)
    {
        if (h>maxh)
            maxh=h;
        return ;
    }
    count(t[p].left,h+1);
    count(t[p].right,h+1);
}

int main()
{
    long n,i,x,y,z,d;
    //n points [ (n-1) edges ] , root number
    //assume that point number is from 1 to n
    printf("The t contains n point(s) and the number of root node is m\n");
    printf("Please input n & m:\n");
    scanf("%ld %ld",&n,&root);
    //0 means subt is NULL
    for (i=1;i<=n;i++)
    {
        t[i].left=0;
        t[i].right=0;
    }
    printf("Please input %ld edge(s)\n",n-1);
    for (i=1;i<n;i++)
    {
        //the father of y is x , x is on the left(1)/right(2)
        scanf("%ld %ld %ld",&x,&y,&z);
        if (z==1)
            t[x].left=y;
        else
            t[x].right=y;
    }
    printf("\n\nPreorder:");
    DLR(root);
    printf("\n\nInorder:");
    LDR(root);
    printf("\n\nPosorder:");
    LRD(root);

    printf("\n\n------------\n\n");
    printf("Test using non recursion to ergodic...\n");
    printf("\n\nPreorder:");
    DLR_NonRecursion(root);
    printf("\n\nInorder:");
    LDR_NonRecursion(root);
    printf("\n\nPosorder:");
    LRD_NonRecursion(root);


    printf("\n\n------------\n\n");

    //change the subtree of point p
    scanf("%ld",&d);
    ChangeSubtree(d);
    printf("After changing the subtree of point %ld...\n",d);
    printf("\n\nPreorder:");
    DLR(root);
    printf("\n\nInorder:");
    LDR(root);
    printf("\n\nPosorder:");
    LRD(root);

    printf("\n\n------------\n\n");

    count(root,0);
    printf("The Height of the tree is %ld\n",maxh);

    return 0;
}
/*
6 1
1 2 1
1 3 2
2 4 1
2 5 2
3 6 1
*/
/*
Preorder:1 2 4 5 3 6

Inorder:4 2 5 1 6 3

Posorder:4 5 2 6 3 1
*/
