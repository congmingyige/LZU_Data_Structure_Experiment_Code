#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define maxn 1000

///二叉树 遍历 每次遍历，加标签，增加子节点到父节点的边(或翻转边的方向)

//静态链表，提前给出对应编号的链表的位置，方便建树
//其实用long left,right是最简单的，没必要用struct node *left,*right,*father;
struct node
{
    long tag;
    long left,right,father;
};

int main()
{
    long n,root,x,y,z,i,d;
    //num:1~n edge:n-1
    scanf("%ld%ld",&n,&root);
    //*tree[maxn+1] in case that maxn is very large
    struct node *tree=(struct node *) malloc (sizeof(struct node )*(maxn+1));
    for (i=1;i<=n;i++)
    {
        tree[i].left=0;
        tree[i].right=0;
    }
    for (i=1;i<n;i++)
    {
        scanf("%ld%ld%ld",&x,&y,&z);
        //left
        if (z==1)
            tree[x].left=y;
        //right
        else if (z==2)
            tree[x].right=y;
    }

    ///DLR
    //insure that 在一棵树中，根先输出
    d=root;
    for (i=1;i<=n;i++)
    {
        tree[i].tag=0;
        tree[i].father=0;
    }
    printf("DLR:\t");
    while (1)
    {
        switch(tree[d].tag)
        {
            case 0:
                printf("%ld ",d);
                if (tree[d].left!=0)
                {
                    tree[d].tag=1;
                    tree[tree[d].left].father=d;
                    d=tree[d].left;
                    continue;
                }
            case 1:
                if (tree[d].right!=0)
                {
                    tree[d].tag=2;
                    tree[tree[d].right].father=d;
                    d=tree[d].right;
                    continue;
                }
            case 2:
//                if (tree[d].father!=0)
                    d=tree[d].father;
//                else
//                    break;
        }
        if (d==0)
            break;
    }
    printf("\n");

    ///LDR
    //insure that 在一棵树中，左子树先输出
    d=root;
    for (i=1;i<=n;i++)
    {
        tree[i].tag=0;
        tree[i].father=0;
    }
    printf("LDR:\t");
    while (1)
    {
        switch(tree[d].tag)
        {
            case 0:
                if (tree[d].left!=0)
                {
                    tree[d].tag=1;
                    tree[tree[d].left].father=d;
                    d=tree[d].left;
                    continue;
                }
            case 1:
                printf("%ld ",d);
                if (tree[d].right!=0)
                {
                    tree[d].tag=2;
                    tree[tree[d].right].father=d;
                    d=tree[d].right;
                    continue;
                }
            case 2:
//                if (tree[d].father!=0)
                    d=tree[d].father;
//                else
//                    break;
        }
        if (d==0)
            break;
    }
    printf("\n");

    ///LRD
    //insure that 在一棵树中，右子树先输出
    d=root;
    for (i=1;i<=n;i++)
    {
        tree[i].tag=0;
        tree[i].father=0;
    }
    printf("LRD:\t");
    while (1)
    {
        switch(tree[d].tag)
        {
            case 0:
                if (tree[d].left!=0)
                {
                    tree[d].tag=1;
                    tree[tree[d].left].father=d;
                    d=tree[d].left;
                    continue;
                }
            case 1:
                if (tree[d].right!=0)
                {
                    tree[d].tag=2;
                    tree[tree[d].right].father=d;
                    d=tree[d].right;
                    continue;
                }
            case 2:
                printf("%ld ",d);
//                if (tree[d].father!=0)
                    d=tree[d].father;
//                else
//                    break;
        }
        if (d==0)
            break;
    }
    printf("\n");


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
