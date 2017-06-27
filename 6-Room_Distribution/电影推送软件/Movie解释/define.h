#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

const long max_user=10000;
const long max_movie=10000;
const long maxlen=20;
const long max_review=100;
const long max_address=100;
extern

char quality[15]={"1080p","720p","mkv","mp3"};
http://zhidao.baidu.com/link?url=TExsbOLSpJ3K9iEwokYi2dwF5AU-a54Ij1nI3mtTfO5c6wzVHRDbuAVBsnI9jvAkp3aWjDT0-9clLsR62EWhM_
//		心情不好时看的电影  //心情低落看什么电影
char c_mood[30]={"伤心","担心","高兴",};

//   主题 心情恢复   身心健康……   患者  恢复
//豆瓣

struct user
{
    char name[maxlen],password[maxlen];
    int Sex,Define,Age,Condition,Preference;
//Sex 男:1 女:2 不填:0
//Define 学生:1 工作者:2 其它:3 不填:0
//Age 未成年:1 青年人:2 成年人:3 老人:4 不填:0
//Condition 放假:1 考试:2 康复:3 不填:0
//Preference 不同类别:1~9 不填:0
};

struct download
{
    char file[max_address],download_file[max_address],download_website[max_address],file_size[10];
    float ;
    int quality;
};

//把电影下载了，别人可以从自己机子处下载东西
struct movie
{
    float rating,rating_user[max_user];
    char review,review[max_user][max_review];
    struct download download[10];
    int category[5];
};

struct user user[max_user];
struct movie movie[max_movie];

//专题 高考季,爆笑娱乐……

#endif // DEFINE_H_INCLUDED
