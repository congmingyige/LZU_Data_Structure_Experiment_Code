#include <stdio.h>
#include <stdlib.h>
#define maxn 1000

struct node
{
    long value;
    struct node *left,*right;
}*t[maxn+1];
long root;

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
    struct node *temp;
    temp=p->left;
    p->left=p->right;
    p->right=temp;
    if (p->left!=NULL)
        ChangeSubTree(p->left);
    if (p->right!=NULL)
        ChangeSubTree(p->right);
}


int main()
{
    long n,i,x,y,z;
    //n points [ (n-1) edges ] , root number
    //assume that point number is from 1 to n
    printf("The t contains n point(s) and the number of root node is m\n");
    printf("Please input n & m:\n");
    scanf("%ld %ld",&n,&root);
    //init
    for (i=1;i<=n;i++)
    {
        t[i]=(struct node *) malloc (sizeof(struct node));
        t[i]->value=i;
        t[i]->left=NULL;
        t[i]->right=NULL;
    }
    printf("Please input %ld edge(s)\n",n-1);
    for (i=1;i<n;i++)
    {
        //the father of y is x , x is on the left(1)/right(2)
        scanf("%ld %ld %ld",&x,&y,&z);
        if (z==1)
            t[x]->left=t[y];
        else
            t[x]->right=t[y];
    }
    printf("Height=%ld\n\n",TreeHeight(t[root]));

    printf("\n\nPreorder:");
    DLR(t[root]);
    printf("\n\nInorder:");
    LDR(t[root]);
    printf("\n\nPosorder:");
    LRD(t[root]);

    //该接点为根接点的树的所有的左右子树都交换
    ChangeSubTree(t[root]);
    printf("\n\nAfter changing the subtree of point %ld\t...",root);
    printf("\n\nPreorder:");
    DLR(t[root]);
    printf("\n\nInorder:");
    LDR(t[root]);
    printf("\n\nPosorder:");
    LRD(t[root]);

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
