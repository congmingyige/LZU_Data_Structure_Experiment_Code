#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#define maxn 100000
#define maxx 100
#define maxy 1000
#define maxz 10

struct node
{
    char name[50];
    long age;
    long sex;
    long yy,mm,dd;
    long grade;
    long room_number;
    long bed_number;
}*info[maxn+1];

long amount[maxx+1][maxy+1],f[maxx+1][maxy+1][maxz+1];
bool vis[maxx+1][maxy+1][maxz+1];

//用于回收
long stack[maxn+1],sum;




/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC         hdc;  //设备环境句柄
    PAINTSTRUCT ps;
    RECT        rect;

    switch (message){
        //窗口绘制消息
        case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps) ;
            GetClientRect (hwnd, &rect) ;
            DrawText(
                hdc,
                TEXT("你好，欢迎来到C语言中文网"),
                -1,
                &rect,
                DT_SINGLELINE | DT_CENTER | DT_VCENTER
            );
            EndPaint (hwnd, &ps) ;
            return 0 ;

        //窗口销毁消息
        case WM_DESTROY:
            PostQuitMessage(0) ;
            return 0 ;
    }
    return DefWindowProc(hwnd, message, wParam, lParam) ;
}

void Properties()
{
    long i,j,x,y,z;
    char c;
    for (i=1;i<=maxx+1;i++)
        for (j=1;j<=maxy+1;j++)
            amount[i][j]=-1;

    FILE *in=fopen("Properties.csv","r");
    while ()
    {
        //fscanf("%ld%c%ld%c%ld",&x,&c,&y,&c,&z)
        amount[x][y]=z;
        for (j=1;j<=z;j++)
            vis[x][y][z]=false;
    }
    fclose(in);
}

//void load()
//{
//    FILE *in=fopen("info.txt","r");
//    while (fscanf("%s%ld%ld%ld%ld%ld%ld"))
//    fclose(in);
//}

//void clsinfo()
//{
//    sum=0;
//}

void User()
{
    //printf("Please input ");
}

void Employee()
{

}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    long mode_person;
    FILE *out=fopen("info.txt","w");
    Properties();
//    load();
    while (1)
    {
        system("cls");
        printf("1:  User\n");
        printf("2:  Employee\n");
        switch(mode_person)
        {
            case 1:
                User();
            case 2:
                Employee();
            default:
                break;
        }
    }




    static TCHAR szClassName[] = TEXT("HelloWin");  //窗口类名
    HWND     hwnd;  //窗口句柄
    MSG      msg;  //消息
    WNDCLASS wndclass;  //窗口类

    /**********第①步：注册窗口类**********/
    //为窗口类的各个字段赋值
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //窗口风格
    wndclass.lpfnWndProc  = WndProc;  //窗口过程
    wndclass.cbClsExtra   = 0;  //暂时不需要理解
    wndclass.cbWndExtra   = 0;  //暂时不需要理解
    wndclass.hInstance    = hInstance;  //当前窗口句柄
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //窗口图标
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW);  //鼠标样式
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);  //窗口背景画刷
    wndclass.lpszMenuName = NULL ;  //窗口菜单
    wndclass.lpszClassName= szClassName;  //窗口类名

    //注册窗口
    RegisterClass(&wndclass);

    /*****第②步：创建窗口(并让窗口显示出来)*****/
    hwnd = CreateWindow(
        szClassName,  //窗口类的名字
        TEXT("Welcome"),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        CW_USEDEFAULT,  //初始化时x轴的位置
        CW_USEDEFAULT,  //初始化时y轴的位置
        500,  //窗口宽度
        300,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );

    //显示窗口
    ShowWindow (hwnd, iCmdShow);
    //更新（绘制）窗口
    UpdateWindow (hwnd);

    /**********第③步：消息循环**********/
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage (&msg);  //分派消息
    }

    return msg.wParam;
}
