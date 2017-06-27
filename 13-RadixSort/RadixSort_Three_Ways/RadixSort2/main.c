#include <stdio.h>
#include <stdlib.h>
//����
#define maxn 1000
//���ķ�Χ x~y
#define x 0
#define y 9
//�ؼ��ָ���
#define g 3

//n������ÿ������g���ؼ���
//������һ�λ�������(Ͱ����)�󣬽����������
//�����ڣ�2~3���ؼ��֣���һ���ؼ��ֵķ�Χ�ϴ��ҷֲ���Ϊ��ɢ��
    //ͨ����һ���ؼ��ְ����ֳ����ɸ����������Ĵ�С��С���Ӷ�ÿ�����������ʱ��Ҳ��С

struct node
{
    //�ؼ��ֵ�ֵ
    long key[g+1];
}data[maxn+1],f[maxn+1];
//next:��һ�����ı��
//front,rear:һ���������,β���ݵı��
long next[maxn+1],front[y-x+1],rear[y-x+1];

void qsort_(long l,long r)
{
    long i,j,p,q;
    struct node t;
    i=l; j=r; p=f[(l+r)>>1].key[2]; q=f[(l+r)>>1].key[3];
    while (i<=j)
    {
        while (f[i].key[2]<p || (f[i].key[2]==p && f[i].key[3]<q)) i++;
        while (f[j].key[2]>p || (f[j].key[2]==p && f[j].key[3]>q)) j--;
        if (i<=j)
        {
            t=f[i];
            f[i]=f[j];
            f[j]=t;
            i++;
            j--;
        }
    }
    if (i<r) qsort_(i,r);
    if (j>l) qsort_(l,j);
}

int main()
{
    long n,i,j,head,pos,value,b;
    scanf("%ld",&n);
    for (i=1;i<=n;i++)
        for (j=1;j<=g;j++)
            scanf("%ld",&data[i].key[j]);
    for (i=1;i<n;i++)
        next[i]=i+1;
    next[n]=0;
    head=1;
    ///key 1

    //ֵΪj��������׵�ַ��0����j����û��Ԫ��
    for (j=x;j<=y;j++)
        front[j]=0;
    pos=head;
    ///����
    while (pos)
    {
        //��һ������ӵ�value�����ĩβ
        value=data[pos].key[1];
        //���ԭ��value������Ԫ�أ���ԭ��value�����ĩβԪ�صĺ��Ϊ��pos����
        //���ԭ��value����û��Ԫ�أ���value�������ʼԪ��Ϊ��pos����
        if (front[value]!=0)
            next[rear[value]]=pos;
        else
            front[value]=pos;
        //��ǰvalue�����ĩβԪ��Ϊ��pos����
        rear[value]=pos;
        pos=next[pos];
    }
    ///�ռ�
    printf("\n");
    j=0;
    for (i=x;i<=y;i++)
        if (front[i]!=0)
        {
            b=j+1;
            pos=front[i];
            while (pos!=rear[i])
            {
                j++;
                f[j]=data[pos];
                pos=next[pos];
            }
            j++;
            f[j]=data[pos];
            qsort_(b,j);
        }
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=g;j++)
            printf("%ld ",f[i].key[j]);
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

