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
//		���鲻��ʱ���ĵ�Ӱ  //������俴ʲô��Ӱ
char c_mood[30]={"����","����","����",};

//   ���� ����ָ�   ���Ľ�������   ����  �ָ�
//����

struct user
{
    char name[maxlen],password[maxlen];
    int Sex,Define,Age,Condition,Preference;
//Sex ��:1 Ů:2 ����:0
//Define ѧ��:1 ������:2 ����:3 ����:0
//Age δ����:1 ������:2 ������:3 ����:4 ����:0
//Condition �ż�:1 ����:2 ����:3 ����:0
//Preference ��ͬ���:1~9 ����:0
};

struct download
{
    char file[max_address],download_file[max_address],download_website[max_address],file_size[10];
    float ;
    int quality;
};

//�ѵ�Ӱ�����ˣ����˿��Դ��Լ����Ӵ����ض���
struct movie
{
    float rating,rating_user[max_user];
    char review,review[max_user][max_review];
    struct download download[10];
    int category[5];
};

struct user user[max_user];
struct movie movie[max_movie];

//ר�� �߿���,��Ц���֡���

#endif // DEFINE_H_INCLUDED
