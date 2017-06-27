#include <stdio.h>
#include <stdlib.h>

int main()
{
	//n个人，每m个人除去一个人，求k轮除去的人的编号
	//f[n][k]可以分为（第一轮报数）+（n-1个人报k-1轮）
	//f[n][k]为第一轮报数的编号的基础上加上n-1个人在第k-1轮除去的人的编号
	//f[n][k]=(f[n-1][k-1]+m) % n
	//f[n-k+1][1]=m-1
	int n,m,k,i,x;
	scanf("%d%d%d",&n,&m,&k);
	x=(m-1)%(n-k+1);
	//编号认为从0~n-1;因为若为1~n，%n有可能出现0的情况，不太好
	for (i=n-k+2;i<=n;i++)
		x=(x+m)%i;
	printf("%d\n",x+1);
	return 0;
}
