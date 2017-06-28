#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define maxn 1000

struct node
{
    long value;
    struct node *left,*right;
}*t[maxn+1];
long maxh=0,root;

//前序遍历
void DLR(struct node *p)
{
    printf("%ld ",p->value);
    if (p->left!=NULL)
        DLR(p->left);
    if (p->right!=NULL)
        DLR(p->right);
}

//中序遍历
void LDR(struct node *p)
{
    if (p->left!=NULL)
        LDR(p->left);
    printf("%ld ",p->value);
    if (p->right!=NULL)
        LDR(p->right);
}

//后序遍历
void LRD(struct node *p)
{
    if (p->left!=0)
        LRD(p->left);
    if (p->right!=0)
        LRD(p->right);
    printf("%ld ",p->value);
}

/*
汇编：
子函数
call
ret

用静态链表
.left,.right为地址
非递归遍历：注意push,pop的内容固定长度，为2个字节
*/

/*
找到递归转非递归的普遍方法(多层递归)，做一个转换程序(器)
*/

//直译
void DLR_NonRecursion(struct node *p)
{
    if (p==NULL)
    {
        printf("Empty Tree\n");
        return ;
    }
    long cond[maxn+1],count;
    struct node *stack[maxn+1];

    count=1;
    stack[1]=p;
    cond[1]=0;

    while (count!=0)
    {
        if (cond[count]==0)
        {
            printf("%ld ",stack[count]->value);
            cond[count]=1;
            if (stack[count]->left!=NULL)
            {
                count++;
                stack[count]=stack[count-1]->left;
                cond[count]=0;
            }
        }
        else
        {
            //del & add
            if (stack[count]->right!=NULL)
            {
                stack[count]=stack[count]->right;
                cond[count]=0;
            }
            else
                count--;
        }
    }
}

void LDR_NonRecursion(struct node *p)
{
    if (p==NULL)
    {
        printf("Empty Tree\n");
        return ;
    }
    long cond[maxn+1],count;
    struct node *stack[maxn+1];

    count=1;
    stack[1]=p;
    cond[1]=0;

    while (count!=0)
    {
        if (cond[count]==0)
        {
            cond[count]=1;
            if (stack[count]->left!=NULL)
            {
                count++;
                stack[count]=stack[count-1]->left;
                cond[count]=0;
            }
        }
        else
        {
            printf("%ld ",stack[count]->value);
            if (stack[count]->right!=NULL)
            {
                stack[count]=stack[count]->right;
                cond[count]=0;
            }
            else
                count--;
        }
    }
}

void LRD_NonRecursion(struct node *p)
{
    if (p==NULL)
    {
        printf("Empty Tree\n");
        return ;
    }
    long cond[maxn+1],count;
    struct node *stack[maxn+1];

    count=1;
    stack[1]=p;
    cond[1]=0;

    while (count!=0)
    {
        if (cond[count]==0)
        {
            cond[count]=1;
            if (stack[count]->left!=NULL)
            {
                count++;
                stack[count]=stack[count-1]->left;
                cond[count]=0;
            }
        }
        else if (cond[count]==1)
        {
            cond[count]=2;
            if (stack[count]->right!=NULL)
            {
                count++;
                stack[count]=stack[count-1]->right;
                cond[count]=0;
            }
        }
        else
        {
            printf("%ld ",stack[count]->value);
            count--;
        }
    }
}

//允许空指针入栈
void DLR_1(struct node *p)
{
    if (p==NULL)
    {
        printf("Empty Tree\n");
        return ;
    }

    long count=0;
    struct node *stack[maxn+1];
    do
    {
        while (p!=NULL)
        {
            count++;
            stack[count]=p;
            printf("%ld ",p->value);
            p=p->left;
        }
        //这里是处理右子树为空的结点，因为这些结点没有必要处理
        while (count!=0 && stack[count]->right==NULL)
            count--;
        if (count!=0)
        {
            p=stack[count]->right;
            count--;
        }
    }
    while (p!=NULL || count!=0);
}

void LDR_1(struct node *p)
{
    if (p==NULL)
    {
        printf("Empty Tree\n");
        return ;
    }

    long count=0;
    struct node *stack[maxn+1];
    do
    {
        while (p!=NULL)
        {
            count++;
            stack[count]=p;
            p=p->left;
        }
        while (count!=0 && stack[count]->right==NULL)
        {
            printf("%ld ",stack[count]->value);
            count--;
        }
        if (count!=0)
        {
            printf("%ld ",stack[count]->value);
            p=stack[count]->right;
            count--;
        }
    }
    while (p!=NULL || count!=0);
}

void LRD_1(struct node *p)
{
    if (p==NULL)
    {
        printf("Empty Tree\n");
        return ;
    }

    long count=0;
    struct node *stack[maxn+1];
    bool vis[maxn+1];
    do
    {
        while (p!=NULL)
        {
            count++;
            stack[count]=p;
            vis[count]=false;
            p=p->left;
        }
        //当该结点的左右子树都访问过(这里的访问包括该结点的右子树为空，不用访问)，输出该结点
        while (count!=0 && (stack[count]->right==NULL || vis[count]==true))
        {
            printf("%ld ",stack[count]->value);
            count--;
        }
        if (count!=0)
        {
            p=stack[count]->right;
            vis[count]=true;
            //这里没有出栈，只是设置该结点的左子树已访问过
                //270行(while……)，输出节点，并出栈
        }
    }
    while (p!=NULL || count!=0);
}

void DLR_2(struct node *p)
{
    if (p==NULL)
    {
        printf("Empty Tree\n");
        return ;
    }

    long count=0;
    struct node *stack[maxn+1];
    do
    {
        while (p!=NULL)
        {
            count++;
            stack[count]=p;
            printf("%ld ",p->value);
            p=p->left;
        }
        if (count!=0)
        {
            p=stack[count]->right;
            count--;
        }
    }
    while (p!=NULL || count!=0);
}

void LDR_2(struct node *p)
{
    if (p==NULL)
    {
        printf("Empty Tree\n");
        return ;
    }

    long count=0;
    struct node *stack[maxn+1];
    do
    {
        while (p!=NULL)
        {
            count++;
            stack[count]=p;
            p=p->left;
        }
        if (count!=0)
        {
            printf("%ld ",stack[count]->value);
            p=stack[count]->right;
            count--;
        }
    }
    while (p!=NULL || count!=0);
}

void LRD_2(struct node *p)
{
    if (p==NULL)
    {
        printf("Empty Tree\n");
        return ;
    }

    long count=0;
    struct node *stack[maxn+1];
    bool vis[maxn+1];
    do
    {
        while (p!=NULL)
        {
            count++;
            stack[count]=p;
            vis[count]=false;
            p=p->left;
        }
        //当该结点的左右子树都访问过，输出该结点
        while (count!=0 && vis[count]==true)
        {
            printf("%ld ",stack[count]->value);
            count--;
        }
        if (count!=0)
        {
            p=stack[count]->right;
            vis[count]=true;
        }
    }
    while (p!=NULL || count!=0);
}

void ChangeSubtree(struct node *p)
{
    if (p!=NULL)
    {
    	struct node *temp;
    	temp=p->left;
	p->left=p->right;
    	p->right=temp;
    }
}

//统计高度
//或者建树(遍历)时对每一个点处理,height[t[p].left/right]=height[p]+1
void TreeHeight(struct node *p,long h)
{
    if (p==NULL)
    {
        if (h>maxh)
            maxh=h;
        return ;
    }
    TreeHeight(p->left,h+1);
    TreeHeight(p->right,h+1);
}

int main()
{
    long n,i,x,y,z,d;
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
    printf("\n\nPreorder:");
    DLR(t[root]);
    printf("\n\nInorder:");
    LDR(t[root]);
    printf("\n\nPosorder:");
    LRD(t[root]);

    printf("\n\n------------\n\n");


    printf("Test using non recursion to ergodic...(Way1)\n");
    printf("\n\nPreorder:");
    DLR_NonRecursion(t[root]);
    printf("\n\nInorder:");
    LDR_NonRecursion(t[root]);
    printf("\n\nPosorder:");
    LRD_NonRecursion(t[root]);


    printf("\n\n------------\n\n");


    printf("Test using non recursion to ergodic...(Way2)\n");
    printf("\n\nPreorder:");
    DLR_1(t[root]);
    printf("\n\nInorder:");
    LDR_1(t[root]);
    printf("\n\nPosorder:");
    LRD_1(t[root]);


    printf("\n\n------------\n\n");


    printf("Test using non recursion to ergodic...(Way3)\n");
    printf("\n\nPreorder:");
    DLR_2(t[root]);
    printf("\n\nInorder:");
    LDR_2(t[root]);
    printf("\n\nPosorder:");
    LRD_2(t[root]);


    printf("\n\n------------\n\n");


    printf("Test using non recursion to ergodic...(Way4-change the position of edge)\n");
    //not used in current study


    printf("\n\n------------\n\n");



    TreeHeight(t[root],0);
    printf("The Height of the tree is %ld\n",maxh);


    printf("\n\n------------\n\n");

    //change the subtree of point p
    printf("Please input point d(ChangeSubtree):\t");
    scanf("%ld",&d);
    ChangeSubtree(t[d]);
    printf("After changing the subtree of point %ld\t...",d);
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
/*
10 1
1 2 1
1 3 2
2 4 1
2 5 2
3 9 2
4 6 1
5 8 2
9 10 1
6 7 2

*/
