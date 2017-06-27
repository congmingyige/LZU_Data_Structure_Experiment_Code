#include <stdio.h>
#include <stdlib.h>
#define maxn 1000
#define LONG_MAX 2000000000

//A中输出的数：B,C不全有
//不排除A中相同的元素

long cmp(const void *a,const void *b)
{
    return *(long *)a-*(long *)b;
}

int main()
{
    //+1: for safety
    long a[maxn+1],b[maxn+1],c[maxn+1],d[maxn+1],ansa,ansb,ansc,ansd,i,j,k;
    //下标为0开始，方便使用qsort
    printf("Linear List A:\n");
    scanf("%ld",&ansa);
    for (i=0;i<ansa;i++)
        scanf("%ld",&a[i]);

    printf("Linear List B:\n");
    scanf("%ld",&ansb);
    for (i=0;i<ansb;i++)
        scanf("%ld",&b[i]);

    printf("Linear List C:\n");
    scanf("%ld",&ansc);
    for (i=0;i<ansc;i++)
        scanf("%ld",&c[i]);

    //使a,b,c变为有序表(元素是按照升序/降序排列的)
    qsort(a,ansa,sizeof(long),cmp);
    qsort(b,ansb,sizeof(long),cmp);
    qsort(c,ansc,sizeof(long),cmp);

    j=0;
    k=0;
    ansd=0;
    //使数组b/c的最后一个数不等于数组a中的任意一个数
    b[ansb]=LONG_MAX;
    c[ansc]=LONG_MAX;
    //把A删除b、c的公共元素之后 的部分存入D
    for (i=0;i<ansa;i++)
    {
        //在B/C数组中找到第一个大于等于a[i]的数(或者找不到)
        //要把j<ansb放在前面，作用是判断j的下标是否在数组使用范围内
        while (j<ansb && b[j]<a[i])
            j++;
        while (k<ansc && c[k]<a[i])
            k++;
        if (b[j]!=c[k] || a[i]!=b[j])
        {
            d[ansd]=a[i];
            ansd++;
        }
    }
    //题目要求建立有序表D，所以没有不创建数组，直接输出
    printf("Linear List D:\n");
    for (i=0;i<ansd;i++)
        printf("%ld ",d[i]);
    printf("\n");
    return 0;
}
/*
Input:
6
1 2 3 1 4 5
4
2 3 4 7
4
5 4 3 7
Output:
1 1 2 5
*/
/*
Input:
6
1 3 2 4 4 5
2
3 4
4
1 4 4 5
Output:
1 2 3 5
*/
