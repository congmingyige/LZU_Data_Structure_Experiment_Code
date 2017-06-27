#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;
    struct student
    {
        char name[50],department[50];
        long basepay,allowance,total;
    }info[1000];
    long num=0,i;
    char s[100];
    fp=fopen("paydata.txt","w");
    while (gets(s))
    {
        //输入Enter，s不变,s[0]='\0',退出
        if (s[0]=='\0')
            break;
        fprintf(fp,"%s\n",s);
        s[0]='\0';
    }
    fclose(fp);
    fp=fopen("paydata.txt","r");
    while (1)
    {
        fscanf(fp,"%s%s%ld%ld%ld",info[num].name,info[num].department,
            &info[num].basepay,&info[num].allowance,&info[num].total);
        if (strcmp(info[num].name,"")==0)
            break;
        info[num].basepay+=100;
        info[num].total+=100;
        num++;
    }
    fclose(fp);
    printf("%ld person(s):\n",num);
    for (i=0;i<num;i++)
        printf("%ld : %s %s %ld  %ld %ld\n",i+1,info[i].name,info[i].department,
            info[i].basepay,info[i].allowance,info[i].total);
    return 0;
}
/*
chen GZ 5000 2000 7000
Li SH 4500 3000 7500
Wang BJ 3000 3000 6000
*/
