#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#define maxn 1000

void check(level,a,b);

//多台设备：info存储信息(主机)，服务器提供平台，transfer传输交互数据
//快速化半自动设置界面(针对不同酒店，时间)

struct node
{
    bool vis,clean;
    char name[51];
    long age,sex,y,m,d,level,x,y;
};

struct cleantime
{
    long y,m,d;
};

long n,a[maxn],b[maxn],ansclean;
struct node ***f;
struct node cleantime[10000];
struct node endtime[10000];
long ***use;

void distribution()
{
    bool v=false,back=true;
    printf("Please Input Name: ");
    //限制输入长度
    scanf("%50s",name);
    printf("Please Input Age: ");
    scanf("%ld",&age);
    printf("Please Input Sex(0:Male,1:Female ");
    scanf("%ld",&sex);
    while (1)
    {
        for (i=1;i<=n;i++)
        printf("Please Input Room Level");
        scanf("%ld",&level);
        printf("Please choose distribution(0) or select(1): ")
        scanf("%ld",&chmode);
        if (chmode==0)
        {

            for (if[level][x][y].vis=true;=1;i<=a[level];i++)
                for (j=1;j<=b[level];j++)
                    if (f[level][i][j].vis==true && f[level][i][j].clean)
                    {

                    }

            scanf("Please choose Yes(1) or No(0): ");
            scanf("%ld",&ymode);
            if (ymode)
            {

            }
            //back: choose again!
        }
        else
        {

        }
    }


    while (1)
    {
        printf("Please Input Room Level(1~%ld): ",n);
        while (1)
        {
            scanf("%ld",&level);

        }scanf("%ld",&level);


        for (i=1;i<=;i++)
        printf("Please Input Room Number(1~%ld): ",a[level]);
        scanf("%ld",&x);
        printf("Please Input Room Number(1~%ld): ",b[level]);
        scanf("%ld",&y);
    }


    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo;
    timeinfo = localtime(&rawtime);
    printf("%04X%02X%02X%02X%02X%02X\n",
        1900 + timeinfo->tm_year,
        1 + timeinfo->tm_mon,
        timeinfo->tm_mday,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec
        );
}

void withdraw()
{
    long level,x,y;
    while (1)
    {
        printf("Please Input Room Level , Room number , Bed number:\n");
        scanf("%ld%ld%ld",&level,x,y);
        if (f[level][x][y].vis)
            break;
    }
    //if everything in the room is perfect.
    if (check(level,x,y))
    {
        f[level][x][y].vis=true;

    }
}

bool check(long level,long a,long b)
{
    return true;
}

int main()
{
    long i,mode;
    scanf("%ld",&n);
    for (i=1;i<=n;i++)
        scanf("%ld%ld",&a[i],&b[i]);
    f=(struct node ***) malloc (sizeof(struct node **)*(n+1));
    for (i=1;i<=n;i++)
        f[i]=(struct node **) malloc (sizeof(struct node *)*(a[i]+1));
    for (i=1;i<=n;i++)
        for (j=1;j<=a[i];j++)
            f[i][j]=(struct node *) malloc (sizeof(struct node *)*(b[i]+1));
    for (i=1;i<=n;i++)
        for (j=1;j<=a[i];j++)
            for (k=1;k<=b[i];k++)
            {
                f[i][j][k].vis=true;
                f[i][j][k].vis=true;
            }
    use=(long ***) malloc (sizeof(long **)*(n+1));
    for (i=1;i<=n;i++)
        use[i]=(long **) malloc (sizeof(long *)*(a[i]+1));
    for (i=1;i<=n;i++)
        for (j=1;j<=a[i];j++)
            use[i][j]=(long *) malloc (sizeof(long)*(b[i]+1));
    //use
    //unuse

    //选择特定的房间 在use中查找？？？

    //每次:select 判断特定房间是否可用
    //每次:distribution 判断第一间 可以用的房间/找出所有可用的房间供用户选择

    //用链表，当删除一个房间时，用链表删除。
    //数组 ?????
    use[0]=n;
    for (i=1;i<=n;i++)
    {
        use[i][0]=a[i];
        for (j=1;j<=a[i];j++)
        {
            use[i][0][0]=b[i];
            for (k=1;k<=b[i];k++)
                use[i][j][k]=k;
        }
    }
    while (1)
    {
        //0 //1
        scanf("%d",)



        for (i=1;i<=n;i++)
            for (j=1;j<=a[i];j++)
                for (k=1;k<=b[i];k++)

        printf("Distribution:0  Withdraw:1\n");
        printf("Please choose a mode:   \n");
        scanf("%ld",&mode);
        //distribution
        if (mode==0)
            distribution();
        //withdraw
        else
            withdraw();

        //a clerk
        /*
        clean condition
        modify room information(modify wrong information)
        */
    }
    for (i=1;i<=n;i++)
        for (j=1;j<=a[i];j++)
            free(f[i][j]);
    for (i=1;i<=n;i++)
        free(f[i]);
    free(f);
    //free use
    return 0;
}
