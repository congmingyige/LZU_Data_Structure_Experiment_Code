#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n,m,f[1000],i;
	scanf("%d%d",&n,&m);
	f[1]=0;
	for (i=2;i<=n;i++)
		f[i]=(f[i-1]+m)%i;
	printf("%d\n",f[n]+1);
	return 0;
}
