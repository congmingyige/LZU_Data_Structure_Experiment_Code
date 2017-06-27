#include <stdio.h>
#include <stdlib.h>
#define maxn 10000

long a[maxn+1],n;

void down(long i)
{
    long j,temp;
    while (1)
    {
        j=i<<1;
        if (j>n)
            break;
        if (j!=n && a[j]>a[j+1])
            j++;
        if (a[i]>a[j])
        {
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
        else
            break;
        i=j;
    }
}

int main()
{
    long nn,i;
    scanf("%ld",&n);
    for (i=1;i<=n;i++)
        scanf("%ld",&a[i]);
    for (i=n >>1;i>=1;i--)
        down(i);
    nn=n;
    for (i=1;i<=nn;i++)
    {
        printf("%ld ",a[1]);
        a[1]=a[n];
        n--;
        down(1);
    }
    return 0;
}
