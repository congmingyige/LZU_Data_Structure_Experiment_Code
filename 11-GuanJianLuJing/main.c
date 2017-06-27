#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define maxn 1000

struct node
{
    long d; //��
    long value; //��Ȩֵ
    struct node *next;
}*in[maxn+1],*out[maxn+1];
//in:ĳ����Ϊ�ߵ��յ㣬���ж�Ӧ�ߵ�ʼ��
//out:ĳ����Ϊ�ߵ�ʼ�㣬���ж�Ӧ�ߵ��յ�
//���Ϊk�ıߵ�ʼ����յ�Ϊx[k]��y[k]��ȨֵΪz[k]
//��k�ĳ���Ϊg[k]
//����Ϊq
//ve(early),vl(late),e,l�ֱ�Ϊ�¼����磬������ʱ�䣬����磬������ʱ��
long x[maxn+1],y[maxn+1],z[maxn+1],g[maxn+1],q[maxn+1],ve[maxn+1],vl[maxn+1],e[maxn+1],l[maxn+1];

long max(long a,long b)
{
    if (a>b)
        return a;
    else
        return b;
}

long min(long a,long b)
{
    if (a>b)
        return b;
    else
        return a;
}

int main()
{
    long n,m,head,tail,i,s,t;
    struct node *p;
    scanf("%ld%ld",&n,&m);
    //init
    for (i=1;i<=n;i++)
        g[i]=0;
    for (i=1;i<=m;i++)
    {
        scanf("%ld%ld%ld",&x[i],&y[i],&z[i]);
        g[y[i]]++;
        p=(struct node *) malloc (sizeof(struct node));
        p->d=y[i];
        p->value=z[i];
        p->next=out[x[i]];
        out[x[i]]=p;
    }

    head=0;
    tail=0;
    for (i=1;i<=n;i++)
        if (g[i]==0)
        {
            tail++;
            q[tail]=i;
        }

    //init
    for (i=1;i<=n;i++)
        ve[i]=0;
    while (head<tail)
    {
        head++;
        s=q[head];
        p=out[s];
        while (p!=NULL)
        {
            t=p->d;
            g[t]--;
            ve[t]=max(ve[t],ve[s]+p->value);
            if (g[p->d]==0)
            {
                tail++;
                q[tail]=p->d;
            }
            p=p->next;
        }
    }
    if (tail<n)
    {
        printf("has loop\n");
        exit(1);
    }

    //init
    for (i=1;i<=n;i++)
        vl[i]=2000000000;
    vl[q[tail]]=ve[q[tail]];
    for (i=tail;i>=1;i--)
    {
        s=q[i];
        p=out[s];
        while (p)
        {
            vl[s]=min(vl[s],vl[p->d]-p->value);
            p=p->next;
        }
    }

    for (i=1;i<=m;i++)
    {
        e[i]=ve[x[i]];
        l[i]=vl[y[i]]-z[i];
    }
    for (i=1;i<=m;i++)
        if (e[i]==l[i])
            printf("%ld ",i);
    return 0;
}
/*
9 11
7 9 2
8 9 4
5 7 8
5 8 7
6 8 4
2 5 1
3 5 1
4 6 2
1 2 6
1 3 4
1 4 5
*/
