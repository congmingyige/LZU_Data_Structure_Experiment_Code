#include <stdio.h>
#include <stdlib.h>
#define maxn 1000

struct node
{
    long value;
    struct node *left,*right;
}*t[maxn+1];
struct node *tree;
//long root;

long max(long a,long b)
{
    if (a>b)
        return a;
    else
        return b;
}

void DLR(struct node *p)
{
    if (p==NULL)
        return ;
    printf("%ld ",p->value);
    DLR(p->left);
    DLR(p->right);
}

void LDR(struct node *p)
{
    if (p==NULL)
        return ;
    LDR(p->left);
    printf("%ld ",p->value);
    LDR(p->right);
}

void LRD(struct node *p)
{
    if (p==NULL)
        return ;
    LRD(p->left);
    LRD(p->right);
    printf("%ld ",p->value);
}

long TreeHeight(struct node *p)
{
    if (p==NULL)
        return 0;
    else
        return (max(TreeHeight(p->left),TreeHeight(p->right))+1);
}

void ChangeSubTree(struct node *p)
{
    if (p==NULL)
        return ;
    struct node *temp;
    temp=p->left;
    p->left=p->right;
    p->right=temp;

    ChangeSubTree(p->left);
    ChangeSubTree(p->right);
}

struct node * BuildTree()
{
    long value;
    scanf("%ld",&value);
    if (value==0)
        return NULL;
    else
    {
        struct node *p;
        p=(struct node *) malloc (sizeof(struct node));
        p->value=value;
        p->left=BuildTree();
        p->right=BuildTree();
        return p;
    }
}


///这样做不好，太麻烦
//void BuildTree(struct node *father,long branch)
//{
//    long value;
//    scanf("%ld",&value);
//    if (value==0)
//    {
//        //该树为空
//        if (branch==0)
//        {
//            father=NULL;
//            return ;
//        }
//
//        if (branch==1)
//            father->left=NULL;
//        else
//            father->right=NULL;
//    }
//    else
//    {
//        struct node *p;
//        p=(struct node *) malloc (sizeof(struct node));
//        p->value=value;
//
//        if (branch==0)
//            tree=p;
//        else if (branch==1)
//            father->left=p;
//        else
//            father->right=p;
//
//        BuildTree(p,1);
//        BuildTree(p,2);
//    }
//}

///不能这样做，因为进入新的子程序，父结点不能指向子结点
//void BuildTree(struct node *p)
//{
//    long value;
//    struct node *q,*r;
//    scanf("%ld",&value);
//    if (value==0)
//        p=NULL;
//    else
//    {
//        p->value=value;
//        q=(struct node *) malloc (sizeof(struct node));
//        r=(struct node *) malloc (sizeof(struct node));
//        p->left=q;
//        p->right=r;
//        BuildTree(q);
//        BuildTree(r);
//    }
//}

int main()
{

    //另外的一种建树方法(中序遍历 若左右结点为空则输入0)
    printf("Please input tree in inorder\n");
    tree=BuildTree();
//    BuildTree(NULL,0);

    printf("Height=%ld\n\n",TreeHeight(tree));

    printf("\n\nPreorder:");
    DLR(tree);
    printf("\n\nInorder:");
    LDR(tree);
    printf("\n\nPosorder:");
    LRD(tree);

    //该接点为根接点的树的所有的左右子树都交换
    ChangeSubTree(tree);
    printf("\n\nAfter changing the subtree \t...");
    printf("\n\nPreorder:");
    DLR(tree);
    printf("\n\nInorder:");
    LDR(tree);
    printf("\n\nPosorder:");
    LRD(tree);

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

/*
10 1
1 2 1
2 4 1
4 6 1
6 7 2
2 5 2
5 8 2
1 3 2
3 9 2
9 10 1
*/

/*
1 2 4 6 0 7 0 0 0 5 0 8 0 0 3 0 9 10 0 0 0
*/
