#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main()
{
	struct node
	{
		int num;
		struct node * next;
	};
	struct node *line,*temp,*cur;
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	if (m==1)
	{
		for (i=1;i<=n;i++)
			printf("%d ",i);
		return 0;
	}
	line=(struct node *) malloc (sizeof(struct node));
	//line=new node;
	line->num=1;
	cur=line;
	for (i=2;i<=n;i++)
	{
		temp=(struct node *) malloc (sizeof(struct node));
		//temp=new node;
		temp->num=i;
		line->next=temp;
		line=temp;
	}
	line->next=cur;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<m-1;j++)
			cur=cur->next;
		printf("%d ",cur->next->num);
		cur->next=cur->next->next;
		cur=cur->next;
	}
	return 0;
}
