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
//���򣺴����Ĺؼ��ֿ�ʼ����ǰ�Ĺؼ���
//����+�ռ�
//ÿ���ؼ��ַ���+�ռ���Ҫn+nʱ�䣬������g���ؼ��֣�ʱ�临�Ӷ�ΪO(2ng)��
//��������飬���ݼ�����һ�����䣬������ĳ��Ⱥܳ��������������ڴ��˷��ˡ�
//��������Խ��������⣬�����ݲ���Ҫ�Ⱥ�˳�������ޱ�Ҫ��Ҫ������

struct node
{
    //�ؼ��ֵ�ֵ
    long key[g+1];
}data[maxn+1];
//next:��һ�����ı��
//front,rear:һ���������,β���ݵı��
long next[maxn+1],front[y-x+1],rear[y-x+1];

int main()
{
    char c;
    long n,i,j,head,pos,value,t;
    scanf("%ld",&n);
    for (i=1;i<=n;i++)
    {
        c=getchar();
        for (j=1;j<=g;j++)
        {
            c=getchar();
            data[i].key[j]=c-48;
        }

    }
    for (i=1;i<n;i++)
        next[i]=i+1;
    next[n]=0;
    head=1;
    //key i
    for (i=g;i>=1;i--)
    {
        //ֵΪj��������׵�ַ��0����j����û��Ԫ��
        for (j=x;j<=y;j++)
            front[j]=0;
        pos=head;
        ///����
        while (pos)
        {
            //��һ������ӵ�value�����ĩβ
            value=data[pos].key[i];
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
        //��x����,x+1����,����,y���� ������������k��������һ��Ԫ�صĺ��Ϊk+1����ĵ�һ��Ԫ��
        value=x;
        while (front[value]==0)
            value++;
        head=front[value];
        while (value<=y)
        {
            t=value+1;
            while (front[t]==0 && t<=y)
                t++;
            if (t==y+1)
                break;
            next[rear[value]]=front[t];
            value=t;
        }
        next[rear[value]]=0;
    }
    printf("\n");
    pos=head;
    while (pos)
    {
        for (i=1;i<=g;i++)
            printf("%ld",data[pos].key[i]);
        printf("\n");
        pos=next[pos];
    }
    return 0;
}
/*
input:
10
112
979
385
133
543
685
213
145
911
513
output:
112
133
145
213
385
513
543
685
911
979
*/
