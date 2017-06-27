#include <stdio.h>
#include <stdlib.h>

int main()
{
	int next[1000],n,s,i,j,cur=1;
	scanf("%d%d",&n,&s);
	if (s==1)
	{
		for (i=1;i<=n;i++)
			printf("%d ",i);
		return 0;
	}
	for (i=1;i<n;i++)
		next[i]=i+1;
	next[n]=1;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<s-1;j++)
			cur=next[cur];
		printf("%d ",next[cur]);
		next[cur]=next[next[cur]];
		cur=next[cur];
	}
	return 0;
}
