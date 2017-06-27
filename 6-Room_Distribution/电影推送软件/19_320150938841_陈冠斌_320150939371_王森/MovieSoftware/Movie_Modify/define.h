#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <windows.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

struct user
{
    long Number;
    TCHAR Name[100],Password[100];
    //Sex:�Ա�(��1��Ů2������0)
    //Age:����(��ͯ1��������2��������3������4������0)
    //Preference:ƫ��(ϲ��1������2������3������4������5������6���ƻ�7��ð��8������9������0)
    int Sex,Age,Preference;
};

struct movie
{
    long Number;
    TCHAR Name[100],Place[100],Passage[1000],Photo[100],Torrent[100],File[100];
    int year,month,day;
    //UserNumber:���ֵ�������
    long UserNumber;
    //RatioMark:ר������ռ�ܷ����ı���(0~1)
    //OverallMark:����
    //ProfessorMark:ר������
    //UserMark:�����û����ֵķ���֮��
    float RatioMark,OverallMark,ProfessorMark,UserMark;
    //Category:ģʽ(ϲ��1������2������3������4������5������6���ƻ�7��ð��8������9������0)
    //Mood:����(����1��ʧ��2�����3������4��ȱ������5����������6������0)
    //Sex:�Ա�(��1��Ů2������0)
    //Age:����(��ͯ1��������2��������3������4������0)
    //Condition:״̬(�ٽ�����1������ָ�2������0)
    int Category[10],Mood,Sex,Age,Condition;
};
//��Ӱ���û�����
extern struct user user[1000];
extern struct movie movie[1000];
//��ǰ��Ӱ���û������
extern long pos_movie,pos_user;
//��Ӱ���û����� ��ǰ��¼���û���ţ���û��Ϊ0
extern long total_movie,total_user,CurrentUser;

extern int ModeInterface,ModeNumber;

//ĩβ�ǵ�Ҫ��free(user)
//�ǵó�ʼ��user��movie   ��������

#endif // DEFINE_H_INCLUDED
