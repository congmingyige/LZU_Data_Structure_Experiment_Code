#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//二叉排序树(判断一个数是否出现在一个序列中)
//1.排序：相同的数要加进去
//2.判断某些数是否在一个序列中
//所以当序列加入二叉排序树中，相同的数不必加入
//但是相同的数不必再加入：需要每次都判断两个数是否相同，时间消耗长，反不如让相同的数也加入树中(如果序列中的数基本不相同)

struct node
{
    long d;
    struct node *left;
    struct node *right;
}*tree;

void LDR(struct node *p)
{
    if (p!=NULL)
    {
        LDR(p->left);
        printf("%ld ",p->d);
        LDR(p->right);
    }
}

int main()
{
    struct node *p,*q;
    long n,m,s,i;
    scanf("%ld",&n);
    if (n>=1)
    {
        scanf("%ld",&s);
        tree=(struct node *) malloc (sizeof(struct node));
        tree->d=s;
        tree->left=NULL;
        tree->right=NULL;
    }
    for (i=2;i<=n;i++)
    {
        scanf("%ld",&s);
        p=(struct node *) malloc (sizeof(struct node));
        p=tree;
        while (p)
        {
            if (s<p->d)
            {
                if (p->left!=NULL)
                    p=p->left;
                else
                {
                    q=(struct node *) malloc (sizeof(struct node));
                    q->d=s;
                    q->left=NULL;
                    q->right=NULL;
                    p->left=q;
                    break;
                }
            }
            else
            {
                if (p->right!=NULL)
                    p=p->right;
                else
                {
                    q=(struct node *) malloc (sizeof(struct node));
                    q->d=s;
                    q->left=NULL;
                    q->right=NULL;
                    p->right=q;
                    break;
                }
            }
        }
    }
    scanf("%ld",&m);
    for (i=1;i<=m;i++)
    {
        scanf("%ld",&s);
        if (n==0)
        {
            printf("%ld do not exist\n",s);
            continue;
        }
        p=(struct node *) malloc (sizeof(struct node));
        p=tree;
        while (p!=NULL)
        {
            if (p->d==s)
            {
                printf("%ld exist\n",s);
                break;
            }
            else if (s<p->d)
                p=p->left;
            else
                p=p->right;
        }
        if (p==NULL)
                printf("%ld do not exist\n",s);
    }
    //print tree
    //任意一个结点，左子结点(如果有)的值小于该结点的值，右子结点(如果有)的值大于该结点的值
    //所以采用中序遍历(LDR),对于任意一个结点，输出的先后顺序(不一定相邻)为左子结点，根结点，右子结点
    printf("Ascending Order: ");
    LDR(tree);
    return 0;
}
/*
6
2 6 1 3 3 4
3
1 4 7
*/
