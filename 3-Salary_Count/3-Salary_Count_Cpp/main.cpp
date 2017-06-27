#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


int main()
{
    struct student
    {
        char name[50],department[50];
        long basepay,allowance,total;
    }info[1000];
    long num=0,i;
    char s[100];
    ofstream out("paydata.txt");
    //不能如下面 while(scanf(…))，因为不是文本读入而是键盘输入

    while (gets(s))
    {
        //输入Enter，s不变,s[0]='\0',退出
        if (s[0]=='\0')
            break;
        out<<s<<endl;
        s[0]='\0';
    }
    out.close();
    ifstream in("paydata.txt");
    while (in>>info[num].name>>info[num].department>>
            info[num].basepay>>info[num].allowance>>info[num].total)
    {
        info[num].basepay+=100;
        info[num].total+=100;
        num++;
    }
    in.close();
    cout<<num<<" person(s)"<<endl;
    for (i=0;i<num;i++)
        cout<<i<<" : "<<info[i].name<<" "<<info[i].department<<" "<<
            info[i].basepay<<" "<<info[i].allowance<<" "<<info[i].total<<endl;
    return 0;
}
/*
chen GZ 5000 2000 7000
Li SH 4500 3000 7500
Wang BJ 3000 3000 6000
*/

