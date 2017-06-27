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
    //Sex:性别(男1、女2、不填0)
    //Age:年龄(儿童1、青少年2、中年人3、老人4、不填0)
    //Preference:偏好(喜剧1、爱情2、动作3、动画4、剧情5、悬疑6、科幻7、冒险8、犯罪9、不填0)
    int Sex,Age,Preference;
};

struct movie
{
    long Number;
    TCHAR Name[100],Place[100],Passage[1000],Photo[100],Torrent[100],File[100];
    int year,month,day;
    //UserNumber:评分的总人数
    long UserNumber;
    //RatioMark:专家评分占总分数的比例(0~1)
    //OverallMark:总评
    //ProfessorMark:专家评分
    //UserMark:所有用户评分的分数之和
    float RatioMark,OverallMark,ProfessorMark,UserMark;
    //Category:模式(喜剧1、爱情2、动作3、动画4、剧情5、悬疑6、科幻7、冒险8、犯罪9、不填0)
    //Mood:心情(伤心1、失望2、后悔3、紧张4、缺乏动力5、爱情受伤6、不填0)
    //Sex:性别(男1、女2、不填0)
    //Age:年龄(儿童1、青少年2、中年人3、老人4、不填0)
    //Condition:状态(临近考试1、身体恢复2、不填0)
    int Category[10],Mood,Sex,Age,Condition;
};
//电影、用户数据
extern struct user user[1000];
extern struct movie movie[1000];
//当前电影、用户的序号
extern long pos_movie,pos_user;
//电影、用户总数 当前登录的用户编号，若没有为0
extern long total_movie,total_user,CurrentUser;

extern int ModeInterface,ModeNumber;

//末尾记得要加free(user)
//记得初始化user和movie   在主程序

#endif // DEFINE_H_INCLUDED
