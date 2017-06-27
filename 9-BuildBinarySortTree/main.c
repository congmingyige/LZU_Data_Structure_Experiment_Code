#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//����������(�ж�һ�����Ƿ������һ��������)
//1.������ͬ����Ҫ�ӽ�ȥ
//2.�ж�ĳЩ���Ƿ���һ��������
//���Ե����м�������������У���ͬ�������ؼ���
//������ͬ���������ټ��룺��Ҫÿ�ζ��ж��������Ƿ���ͬ��ʱ�����ĳ�������������ͬ����Ҳ��������(��������е�����������ͬ)

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
    //����һ����㣬���ӽ��(�����)��ֵС�ڸý���ֵ�����ӽ��(�����)��ֵ���ڸý���ֵ
    //���Բ����������(LDR),��������һ����㣬������Ⱥ�˳��(��һ������)Ϊ���ӽ�㣬����㣬���ӽ��
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
