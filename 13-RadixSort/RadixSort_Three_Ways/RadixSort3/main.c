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
//�������ǰ�Ĺؼ��ֿ�ʼ�����Ĺؼ�����������Ҫsort(p,q,w) data[x]~data[y]�ŵ�w���ؼ��֣�
    //Ȼ�������sort(s,t,w+1) [p<=s<=t<=q]
//�÷����ķѴ���ʱ����ڴ棬���Ƽ�

struct node
{
    //�ؼ��ֵ�ֵ
    long key[g+1];
}data[maxn+1],f[maxn+1];
//next:��һ�����ı��
//front,rear:һ���������,β���ݵı��

void sort(long p,long q,long w)
{
    long i,j,head,pos,value,next[maxn+1],front[y-x+1],rear[y-x+1],b[y+1],e[y+1];
    for (i=p;i<q;i++)
        next[i]=i+1;
    next[q]=0;
    head=p;
    //ֵΪj��������׵�ַ��0����j����û��Ԫ��
    for (j=x;j<=y;j++)
        front[j]=0;
    pos=head;
    ///����
    while (pos)
    {
        //��һ������ӵ�value�����ĩβ
        value=data[pos].key[w];
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
    for (i=p;i<=q;i++)
        f[i]=data[i];
    j=p-1;
    for (i=x;i<=y;i++)
        if (front[i]!=0)
        {
            b[i]=j+1;
            pos=front[i];
            while (pos!=rear[i])
            {
                j++;
                data[j]=f[pos];
                pos=next[pos];
            }
            j++;
            data[j]=f[pos];
            e[i]=j;
        }
    if (w!=g)
    {
        for (i=x;i<=y;i++)
            //û��������ֻ��1�����Ͳ�������
            if (front[i]!=0 && b[i]!=e[i])
                sort(b[i],e[i],w+1);
    }
}

int main()
{
    long i,j,n;
    scanf("%ld",&n);
    for (i=1;i<=n;i++)
        for (j=1;j<=g;j++)
            scanf("%ld",&data[i].key[j]);
    sort(1,n,1);
    printf("\n");
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=g;j++)
            printf("%ld ",data[i].key[j]);
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
