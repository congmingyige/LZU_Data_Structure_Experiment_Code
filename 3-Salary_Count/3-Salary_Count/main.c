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
    char s[101];
    fp=fopen("paydata.txt","w");
    //不能while(…!=EOF)，因为不是文本读入而是键盘输入
    //如果以空行(Enter)作为结束标志，则不能用scanf，因为scanf不能检测换行、空格
    while (gets(s))
    {
        //输入Enter，s[0]='\0',退出
        if (s[0]=='\0')
            break;
        //s[0]='\0';//some special environments
        fprintf(fp,"%s\n",s);
        //若不想再输入，想退出时，可以按Ctrl+Z，并回车，则退出while循环
    }
    fclose(fp);
    fp=fopen("paydata.txt","r");
    //feof:文件末尾有空格，name(char[]类型)仍会读入，
    //然后其它的值就为空;若第一个为%ld，则不会读入
    //while (!feof(fp))
    while (fgets(s,101,fp))
    {
        //fscanf(fp,"%s%s%ld%ld%ld",info[num].name,info[num].department,
        //    &info[num].basepay,&info[num].allowance,&info[num].total);
        sscanf(s,"%s%s%ld%ld%ld",info[num].name,info[num].department,
            &info[num].basepay,&info[num].allowance,&info[num].total);
        info[num].basepay+=100;
        info[num].total+=100;
        num++;
    }
    fclose(fp);
    printf("%ld person(s):\n",num);
    for (i=0;i<num;i++)
        printf("%ld : %10s %3s %5ld  %5ld %5ld\n",i+1,info[i].name,info[i].department,
            info[i].basepay,info[i].allowance,info[i].total);
    return 0;
}
/*
chen GZ 5000 2000 7000
Li SH 4500 3000 7500
Wang BJ 3000 3000 6000

*/
//最后的换行用于退出
