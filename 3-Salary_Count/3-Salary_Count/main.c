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
    //����while(��!=EOF)����Ϊ�����ı�������Ǽ�������
    //����Կ���(Enter)��Ϊ������־��������scanf����Ϊscanf���ܼ�⻻�С��ո�
    while (gets(s))
    {
        //����Enter��s[0]='\0',�˳�
        if (s[0]=='\0')
            break;
        //s[0]='\0';//some special environments
        fprintf(fp,"%s\n",s);
        //�����������룬���˳�ʱ�����԰�Ctrl+Z�����س������˳�whileѭ��
    }
    fclose(fp);
    fp=fopen("paydata.txt","r");
    //feof:�ļ�ĩβ�пո�name(char[]����)�Ի���룬
    //Ȼ��������ֵ��Ϊ��;����һ��Ϊ%ld���򲻻����
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
//���Ļ��������˳�
