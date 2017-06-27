#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxlen 100
#define maxn 10000

//Ҫ���ǵ��ʴ�Сд,��China���й���china������

//ʱ�临�Ӷ�O(nlogn*k) kΪ���ʱȽϵ�ƽ������ʱ��
//���������ͬ����Ҫ�Ƚϵ�ĩβ
//����ܶ൥����ͬ��ܶ൥�ʵ�ǰ��ܴ�һ���ֶ���ͬ����ô�ķ�ʱ��ܳ�
//����:n words, m length ,they are same , O(n*n*m)

struct node
{
    long x,y;
    char str[maxlen];
}info[maxn];

int cmp(const void *a,const void *b)
{
    return strcmp((*(struct node *)a).str,(*(struct node *)b).str);
}

int main()
{
    char c,c_;
    long x,y,n,len,s,t,xx,yy;
    //��һ���ַ�Ϊ��һ�У���һ��
    x=1;
    y=1;
    n=0;
    len=0;
    //Ҳ������istringstream�ַ�����
    //��һ/����"Ctrl+Z"����(�ӻ�������)
    while (scanf("%c",&c)!=EOF)
    {
        c_=c;
        //character-processing
        //'-':newly-born
        if (!((c>='a' && c<='z') || (c>='A' && c<='Z') || (c=='-' && len!=0)))
            c=' ';
        if (c==' ')
        {
            if (len!=0)
            {
                info[n].str[len]='\0';
                info[n].x=x;
                info[n].y=y-len;
                n++;
                len=0;
            }
        }
        else
        {
            info[n].str[len]=c;
            len++;
        }

        if (c_=='\n')
        {
            x++;
            y=1;
        }
        else
            y++;
    }
    //�����ԣ��������ĵ���
    if (len!=0)
    {
        info[n].str[len]='\0';
        info[n].x=x;
        info[n].y=y-len;
        n++;
    }
    qsort(info,n,sizeof(struct node),cmp);

    t=0;
    while (t<n)
    {
        s=t;
        xx=info[s].x;
        yy=info[t].y;
        t++;
        while (t<n && strcmp(info[t].str,info[s].str)==0)
        {
            if (info[t].x<xx || (info[t].x==xx && info[t].y<yy))
            {
                xx=info[t].x;
                yy=info[t].y;
            }
            t++;
        }
        printf("%s :\n",info[s].str);
        printf("count:\t%ld\n",t-s);
        printf("first occur:\t%ld %ld\n\n",xx,yy);
    }
    return 0;
}
