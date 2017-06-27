#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include "define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
long mins(long a,long b);

HINSTANCE hInst;
long total_movie,total_user,pos_user,pos_movie;
struct movie movie[1000];
struct user user[1000];
//全局变量-qsort
long ShowMovie[1000];
//历史记录
long total_history;
char history[500][100];
char weekname[7][5]={"日","一","二","三","四","五","六"};
//电影推荐
long total_introduce;
char introduce[500][100];
//显示电影类别
char CategoryName[10][10]={"","喜剧","爱情","动作","动画","剧情","悬疑","科幻","冒险","犯罪/战争"};
//路径
char filename[100];

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    //读入数据
    fileopen_introduce();
    fileopen_history();
    fileopen_movie();
    fileopen_user();

    static TCHAR szClassName[] = TEXT("HelloWin");  //窗口类名
    HWND     hwnd;  //窗口句柄
    MSG      msg;  //消息
    WNDCLASS wndclass;  //窗口类

    hInst=hInstance;

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
    hwnd=CreateWindow(
        szClassName,  //窗口类的名字
        TEXT(""),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        200,  //初始化时x轴的位置
        5,  //初始化时y轴的位置
        1000,  //窗口宽度
        820,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );

    ShowWindow(hwnd,iCmdShow);
    UpdateWindow(hwnd);

    //获得文件路径
    GetModuleFileName(NULL,filename,100);
    *(strstr(filename,"MovieSoftware")+14)='\0';
    //初始化：专家评分显示模式
    SendMessage(hwnd,WM_COMMAND,(WPARAM)11,NULL);

    /**********第③步：消息循环**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage(&msg);  //分派消息
        //观看方式
        switch(msg.message)
        {
            case WM_KEYDOWN:
                //观看方式的选择
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_SHIFT)<0 && GetKeyState('1')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)5,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_SHIFT)<0 && GetKeyState('2')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)6,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_SHIFT)<0 && GetKeyState('3')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)7,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_SHIFT)<0 && GetKeyState('4')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)8,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_SHIFT)<0 && GetKeyState('5')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)9,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_SHIFT)<0 && GetKeyState('6')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)10,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_SHIFT)<0 && GetKeyState('7')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)11,NULL);
                //左右方向键 PageHome PageEnd 修改页数
                if (GetKeyState(VK_HOME)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)14,NULL);
                if (GetKeyState(VK_END)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)15,NULL);
                //PageUP PageDown 修改页数
                if (GetKeyState(VK_PRIOR)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)12,NULL);
                if (GetKeyState(VK_NEXT)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)13,NULL);
                //关闭窗口
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('W')<0)
                    SendMessage(hwnd,WM_DESTROY,NULL,NULL);
                //到达修改页数的文本框
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('P')<0)
                    SendMessage(hwnd,WM_COMMAND,200,NULL);
            break;
        }
    }

    return msg.wParam;
}

/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc,mdc;
    HBITMAP bg;
    RECT rect;
    SYSTEMTIME sys;

    static HPEN hPenRed;
    static HPEN hPenWhite;
    //字体
    static HFONT hFont;
    static HFONT hFontTitle;
    static HFONT hFontNumber;
    //用户体验
    static HWND hBtnUser;
    static HWND hBtnUserInformation;
    static HWND hBtnWatchingHistory;
    //观看方式
    static HWND hLabShowMode;
    static HWND hBtnShowMode1;
    static HWND hBtnShowMode2;
    static HWND hBtnShowMode3;
    static HWND hBtnShowMode4;
    static HWND hBtnShowMode5;
    static HWND hBtnShowMode6;
    static HWND hBtnShowMode7;
    //显示页数,改变页数
    static HWND hBtnPageUp;
    static HWND hBtnPageDown;
    static HWND hBtnPageBegin;
    static HWND hBtnPageEnd;
    static HWND hEditPage;
    static HWND hLabTotalPage;
    //电影显示名字
    static HWND hEditMovieShow[10];
    //电影显示信息
    static HWND hBtnInformationShow[10];
    //细分模式
    static HWND hBtnMode1;
    static HWND hBtnMode2;
    static HWND hBtnMode3;
    static HWND hBtnMode4;
    static HWND hBtnMode5;
    static HWND hBtnMode6;
    static HWND hBtnMode7;
    static HWND hBtnMode8;
    static HWND hBtnMode9;
    //推荐
    static HWND hEditIntroduce;

    TCHAR szTextBuf[100];
    char szHistory[1000],szCategory[100];


    //要定义的部分
    int i,j;
    static bool vis_Page=true;
    //LoginMode:0 未登录 1:已登录
    //Drawp为之前选的部分,Drawq为现在选的部分
    static int LoginMode=1,ShowMode=7,DrawPrevious=2,DrawCurrent=2;
    static int EditPage=1,PreviousPage=1,PosPage=1,TotalPage,PosMovie,TotalMovie,PosIntroduce=0;

    switch(message)
    {
        case WM_CREATE:
            //创建画笔
            hPenRed=CreatePen(PS_SOLID,2,RGB(255,0,0));
            hPenWhite=CreatePen(PS_SOLID,2,RGB(255,255,255));
            //创建字体
            hFont=CreateFont(
                -18,-9,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("宋体")
            );

            hFontTitle=CreateFont(
                -22,-11,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("宋体")
            );

            hFontNumber=CreateFont(
                -28,-14,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("黑体")
            );

            if (LoginMode==1) sprintf(szTextBuf,TEXT("已登录"));
                else sprintf(szTextBuf,TEXT("请登录"));
            hBtnUser=CreateWindow(
                TEXT("button"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                700,20,60,30,
                hWnd,(HMENU)1,hInst,NULL
            );

            hBtnUserInformation=CreateWindow(
                TEXT("button"),TEXT("用户信息"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                780,20,80,30,
                hWnd,(HMENU)2,hInst,NULL
            );
            if (LoginMode==0) ShowWindow(hBtnUserInformation,SW_HIDE);

            hBtnWatchingHistory=CreateWindow(
                TEXT("button"),TEXT("观看历史"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                880,20,80,30,
                hWnd,(HMENU)3,hInst,NULL
            );
            if (LoginMode==0) ShowWindow(hBtnWatchingHistory,SW_HIDE);
            //显示的模式:电影类别、适合心情、上映时间、总体评分、用户评分、专家评分
            hLabShowMode=CreateWindow(
                TEXT("static"),TEXT("观看方式"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                30,50,80,30,
                hWnd,(HMENU)4,hInst,NULL
            );

            hBtnShowMode1=CreateWindow(
                TEXT("button"),TEXT("用户模式"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,90,80,30,
                hWnd,(HMENU)5,hInst,NULL
            );

            hBtnShowMode2=CreateWindow(
                TEXT("button"),TEXT("电影类别"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,130,80,30,
                hWnd,(HMENU)6,hInst,NULL
            );

            hBtnShowMode3=CreateWindow(
                TEXT("button"),TEXT("适合心情"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,170,80,30,
                hWnd,(HMENU)7,hInst,NULL
            );

            hBtnShowMode4=CreateWindow(
                TEXT("button"),TEXT("用户状态"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,210,80,30,
                hWnd,(HMENU)8,hInst,NULL
            );

            hBtnShowMode5=CreateWindow(
                TEXT("button"),TEXT("上映时间"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,250,80,30,
                hWnd,(HMENU)9,hInst,NULL
            );

            hBtnShowMode6=CreateWindow(
                TEXT("button"),TEXT("总体评分"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,290,80,30,
                hWnd,(HMENU)10,hInst,NULL
            );

            hBtnShowMode7=CreateWindow(
                TEXT("button"),TEXT("专家评分"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,330,80,30,
                hWnd,(HMENU)11,hInst,NULL
            );

            hBtnPageUp=CreateWindow(
                TEXT("button"),TEXT("<"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_LEFT | BS_VCENTER,
                800,700,30,30,
                hWnd,(HMENU)12,hInst,NULL
            );

            hBtnPageDown=CreateWindow(
                TEXT("button"),TEXT(">"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_RIGHT | BS_VCENTER,
                900,700,30,30,
                hWnd,(HMENU)13,hInst,NULL
            );

            hBtnPageBegin=CreateWindow(
                TEXT("button"),TEXT("<<"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_LEFT | BS_VCENTER,
                765,700,30,30,
                hWnd,(HMENU)14,hInst,NULL
            );

            hBtnPageEnd=CreateWindow(
                TEXT("button"),TEXT(">>"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_RIGHT | BS_VCENTER,
                935,700,30,30,
                hWnd,(HMENU)15,hInst,NULL
            );

            PosPage=1;
            sprintf(szTextBuf,TEXT("%d"),PosPage);
            hEditPage=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                835,700,60,30,
                hWnd,(HMENU)16,hInst,NULL
            );

            TotalMovie=total_movie;
            TotalPage=TotalMovie/10;
            if (TotalMovie%10!=0) TotalPage++;
            sprintf(szTextBuf,TEXT("总有%d页"),TotalPage);
            hLabTotalPage=CreateWindow(
                TEXT("static"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                765,740,200,30,
                hWnd,(HMENU)17,hInst,NULL
            );

            for (i=0;i<10;i++)
                hEditMovieShow[i]=CreateWindow(
                    TEXT("edit"),TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                    120+(i%5)*170,300+(i/5)*270,150,30,
                    hWnd,NULL,hInst,NULL
                );

            for (i=0;i<10;i++)
                hBtnInformationShow[i]=CreateWindow(
                    TEXT("button"),TEXT(""),
                    WS_CHILD | WS_BORDER | BS_CENTER | BS_VCENTER,
                    120+(i%5)*170,335+(i/5)*270,150,30,
                    hWnd,(HMENU)(18+i),hInst,NULL
                );

            hBtnMode1=CreateWindow(
                TEXT("button"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,370,80,30,
                hWnd,(HMENU)28,hInst,NULL
            );

            hBtnMode2=CreateWindow(
                TEXT("button"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,410,80,30,
                hWnd,(HMENU)29,hInst,NULL
            );

            hBtnMode3=CreateWindow(
                TEXT("button"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,450,80,30,
                hWnd,(HMENU)30,hInst,NULL
            );

            hBtnMode4=CreateWindow(
                TEXT("button"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,490,80,30,
                hWnd,(HMENU)31,hInst,NULL
            );

            hBtnMode5=CreateWindow(
                TEXT("button"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,530,80,30,
                hWnd,(HMENU)32,hInst,NULL
            );

            hBtnMode6=CreateWindow(
                TEXT("button"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,570,80,30,
                hWnd,(HMENU)33,hInst,NULL
            );

            hBtnMode7=CreateWindow(
                TEXT("button"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,610,80,30,
                hWnd,(HMENU)34,hInst,NULL
            );

            hBtnMode8=CreateWindow(
                TEXT("button"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,650,80,30,
                hWnd,(HMENU)35,hInst,NULL
            );

            hBtnMode9=CreateWindow(
                TEXT("button"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,690,80,30,
                hWnd,(HMENU)36,hInst,NULL
            );

            hEditIntroduce=CreateWindow(
                TEXT("static"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                100,700,600,40,
                hWnd,(HMENU)37,hInst,NULL
            );

            //用户体验
            SendMessage(hBtnUser,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnUserInformation,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnWatchingHistory,WM_SETFONT,(WPARAM)hFont,NULL);
            //观看方式
            SendMessage(hLabShowMode,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode1,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode2,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode3,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode4,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode5,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode6,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode7,WM_SETFONT,(WPARAM)hFont,NULL);
            //显示页数,改变页数
            SendMessage(hBtnPageUp,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnPageDown,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnPageBegin,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnPageEnd,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditPage,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hLabTotalPage,WM_SETFONT,(WPARAM)hFont,NULL);
            //细分模式
            SendMessage(hBtnMode1,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMode2,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMode3,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMode4,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMode5,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMode6,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMode7,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMode8,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMode9,WM_SETFONT,(WPARAM)hFont,NULL);
            //显示电影名称
            for (i=0;i<10;i++)
                SendMessage(hEditMovieShow[i],WM_SETFONT,(WPARAM)hFont,NULL);
            //显示电影信息
            for (i=0;i<10;i++)
                SendMessage(hBtnInformationShow[i],WM_SETFONT,(WPARAM)hFont,NULL);
            //显示推荐信息
            SendMessage(hEditIntroduce,WM_SETFONT,(WPARAM)hFont,NULL);

            //设置定时器
            SetTimer(hWnd,1,2000,NULL);
            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch (wmId)
            {
                //Ctrl+P
                case 200:
                    GetWindowRect(hEditPage,&rect);
                    SetCursorPos(rect.left,rect.top);
                    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                    mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                    break;
                //用户登录与否
                case 1:
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,"User_Login\\bin\\Debug\\User_Login.exe");
                    system(szTextBuf);
                    break;
                //用户信息
                case 2:
                    fileclose_user_information();
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,"User_Information\\bin\\Debug\\User_Information.exe");
                    system(szTextBuf);
                    fileopen_user_information();
                    //更新界面
                    if (ShowMode==1)
                        SendMessage(hWnd,WM_COMMAND,(WPARAM)5,NULL);
                    break;
                //历史记录
                case 3:
                    sprintf(szHistory,"最近%d个历史记录\n\n",mins(total_history,20));
                    for (i=0;i<mins(total_history,20);i++)
                    {
                        strcat(szHistory,history[i]);
                        strcat(szHistory,"\r\n");
                    }
                    MessageBox(hWnd,szHistory,TEXT("提醒"),MB_OK);
                    break;
                //用户模式
                case 5:
                    ShowWindow(hBtnMode1,SW_HIDE);
                    ShowWindow(hBtnMode2,SW_HIDE);
                    ShowWindow(hBtnMode3,SW_HIDE);
                    ShowWindow(hBtnMode4,SW_HIDE);
                    ShowWindow(hBtnMode5,SW_HIDE);
                    ShowWindow(hBtnMode6,SW_HIDE);
                    ShowWindow(hBtnMode7,SW_HIDE);
                    ShowWindow(hBtnMode8,SW_HIDE);
                    ShowWindow(hBtnMode9,SW_HIDE);
                    //更新矩形 选状态
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=wmId-4;
                    ShowMode=wmId-4;
                    SendMessage(hWnd,WM_PAINT,(WPARAM)wParam,NULL);
                    //显示电影
                    TotalMovie=0;
                    //性别 年龄 电影类别
                    for (i=0;i<total_movie;i++)
                        if (movie[i].Sex==user[pos_user].Sex || movie[i].Age==user[pos_user].Age || movie[i].Category[user[pos_user].Preference]==1)
                        {
                            ShowMovie[TotalMovie]=i;
                            TotalMovie++;
                        }
                    TotalPage=TotalMovie/10;
                    if (TotalMovie%10!=0) TotalPage++;
                    PosPage=1;
                    sprintf(szTextBuf,TEXT("总有%d页"),TotalPage);
                    SetWindowText(hLabTotalPage,szTextBuf);
                    sprintf(szTextBuf,TEXT("%d"),PosPage);
                    SetWindowText(hEditPage,szTextBuf);
                    //这些再按总体评分排序
                    qsort_OverallMark(0,TotalMovie-1);
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    break;
                //电影类别
                case 6:
                    ShowWindow(hBtnMode1,SW_SHOW);
                    ShowWindow(hBtnMode2,SW_SHOW);
                    ShowWindow(hBtnMode3,SW_SHOW);
                    ShowWindow(hBtnMode4,SW_SHOW);
                    ShowWindow(hBtnMode5,SW_SHOW);
                    ShowWindow(hBtnMode6,SW_SHOW);
                    ShowWindow(hBtnMode7,SW_SHOW);
                    ShowWindow(hBtnMode8,SW_SHOW);
                    ShowWindow(hBtnMode9,SW_SHOW);
                    SetWindowText(hBtnMode1,"喜剧");
                    SetWindowText(hBtnMode2,"爱情");
                    SetWindowText(hBtnMode3,"动作");
                    SetWindowText(hBtnMode4,"动画");
                    SetWindowText(hBtnMode5,"剧情");
                    SetWindowText(hBtnMode6,"悬疑");
                    SetWindowText(hBtnMode7,"科幻");
                    SetWindowText(hBtnMode8,"冒险");
                    SetWindowText(hBtnMode9,"犯罪/战争");
                    //更新矩形 选状态
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=wmId-4;
                    ShowMode=wmId-4;
                    SendMessage(hWnd,WM_PAINT,(WPARAM)wParam,NULL);
                    break;
                //适合心情
                case 7:
                    ShowWindow(hBtnMode1,SW_SHOW);
                    ShowWindow(hBtnMode2,SW_SHOW);
                    ShowWindow(hBtnMode3,SW_SHOW);
                    ShowWindow(hBtnMode4,SW_SHOW);
                    ShowWindow(hBtnMode5,SW_HIDE);
                    ShowWindow(hBtnMode6,SW_HIDE);
                    ShowWindow(hBtnMode7,SW_HIDE);
                    ShowWindow(hBtnMode8,SW_HIDE);
                    ShowWindow(hBtnMode9,SW_HIDE);
                    SetWindowText(hBtnMode1,"伤心");
                    SetWindowText(hBtnMode2,"失望");
                    SetWindowText(hBtnMode3,"后悔");
                    SetWindowText(hBtnMode4,"紧张");
                    //更新矩形 选状态
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=wmId-4;
                    ShowMode=wmId-4;
                    SendMessage(hWnd,WM_PAINT,(WPARAM)wParam,NULL);
                    break;
                //用户状态
                case 8:
                    ShowWindow(hBtnMode1,SW_SHOW);
                    ShowWindow(hBtnMode2,SW_SHOW);
                    ShowWindow(hBtnMode3,SW_SHOW);
                    ShowWindow(hBtnMode4,SW_SHOW);
                    ShowWindow(hBtnMode5,SW_HIDE);
                    ShowWindow(hBtnMode6,SW_HIDE);
                    ShowWindow(hBtnMode7,SW_HIDE);
                    ShowWindow(hBtnMode8,SW_HIDE);
                    ShowWindow(hBtnMode9,SW_HIDE);
                    SetWindowText(hBtnMode1,"临近考试");
                    SetWindowText(hBtnMode2,"身体恢复");
                    SetWindowText(hBtnMode3,"缺乏动力");
                    SetWindowText(hBtnMode4,"爱情受伤");
                    //更新矩形 选状态
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=wmId-4;
                    ShowMode=wmId-4;
                    SendMessage(hWnd,WM_PAINT,(WPARAM)wParam,NULL);
                    break;
                //上映时间
                case 9:
                    ShowWindow(hBtnMode1,SW_HIDE);
                    ShowWindow(hBtnMode2,SW_HIDE);
                    ShowWindow(hBtnMode3,SW_HIDE);
                    ShowWindow(hBtnMode4,SW_HIDE);
                    ShowWindow(hBtnMode5,SW_HIDE);
                    ShowWindow(hBtnMode6,SW_HIDE);
                    ShowWindow(hBtnMode7,SW_HIDE);
                    ShowWindow(hBtnMode8,SW_HIDE);
                    ShowWindow(hBtnMode9,SW_HIDE);
                    //更新矩形 选状态
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=wmId-4;
                    ShowMode=wmId-4;
                    SendMessage(hWnd,WM_PAINT,(WPARAM)wParam,NULL);
                    //显示电影
                    TotalMovie=total_movie;
                    TotalPage=TotalMovie/10;
                    if (TotalMovie%10!=0) TotalPage++;
                    PosPage=1;
                    sprintf(szTextBuf,TEXT("总有%d页"),TotalPage);
                    SetWindowText(hLabTotalPage,szTextBuf);
                    sprintf(szTextBuf,TEXT("%d"),PosPage);
                    SetWindowText(hEditPage,szTextBuf);
                    //按上映时间评分排序
                    for (i=0;i<TotalMovie;i++)
                        ShowMovie[i]=i;
                    qsort_Time(0,TotalMovie-1);
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    break;
                //总体评分
                case 10:
                    ShowWindow(hBtnMode1,SW_HIDE);
                    ShowWindow(hBtnMode2,SW_HIDE);
                    ShowWindow(hBtnMode3,SW_HIDE);
                    ShowWindow(hBtnMode4,SW_HIDE);
                    ShowWindow(hBtnMode5,SW_HIDE);
                    ShowWindow(hBtnMode6,SW_HIDE);
                    ShowWindow(hBtnMode7,SW_HIDE);
                    ShowWindow(hBtnMode8,SW_HIDE);
                    ShowWindow(hBtnMode9,SW_HIDE);
                    //更新矩形 选状态
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=wmId-4;
                    ShowMode=wmId-4;
                    SendMessage(hWnd,WM_PAINT,(WPARAM)wParam,NULL);
                    //显示电影
                    TotalMovie=total_movie;
                    TotalPage=TotalMovie/10;
                    if (TotalMovie%10!=0) TotalPage++;
                    PosPage=1;
                    sprintf(szTextBuf,TEXT("总有%d页"),TotalPage);
                    SetWindowText(hLabTotalPage,szTextBuf);
                    sprintf(szTextBuf,TEXT("%d"),PosPage);
                    SetWindowText(hEditPage,szTextBuf);
                    //按总体评分排序
                    for (i=0;i<TotalMovie;i++)
                        ShowMovie[i]=i;
                    qsort_OverallMark(0,TotalMovie-1);
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    break;
                //专家评分
                case 11:
                    ShowWindow(hBtnMode1,SW_HIDE);
                    ShowWindow(hBtnMode2,SW_HIDE);
                    ShowWindow(hBtnMode3,SW_HIDE);
                    ShowWindow(hBtnMode4,SW_HIDE);
                    ShowWindow(hBtnMode5,SW_HIDE);
                    ShowWindow(hBtnMode6,SW_HIDE);
                    ShowWindow(hBtnMode7,SW_HIDE);
                    ShowWindow(hBtnMode8,SW_HIDE);
                    ShowWindow(hBtnMode9,SW_HIDE);
                    //更新矩形 选状态
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=wmId-4;
                    ShowMode=wmId-4;
                    SendMessage(hWnd,WM_PAINT,(WPARAM)wParam,NULL);
                    //显示电影
                    TotalMovie=total_movie;
                    TotalPage=TotalMovie/10;
                    if (TotalMovie%10!=0) TotalPage++;
                    PosPage=1;
                    sprintf(szTextBuf,TEXT("总有%d页"),TotalPage);
                    SetWindowText(hLabTotalPage,szTextBuf);
                    sprintf(szTextBuf,TEXT("%d"),PosPage);
                    SetWindowText(hEditPage,szTextBuf);
                    //按专家评分排序
                    for (i=0;i<TotalMovie;i++)
                        ShowMovie[i]=i;
                    qsort_ProfessorMark(0,TotalMovie-1);
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    break;
                //PageUp
                case 12:
                    if (PosPage!=1)
                    {
                        PosPage--;
                        sprintf(szTextBuf,TEXT("%d"),PosPage);
                        SetWindowText(hEditPage,szTextBuf);
                        SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    }
                    break;
                //PageDown
                case 13:
                    if (PosPage!=TotalPage)
                    {
                        PosPage++;
                        sprintf(szTextBuf,TEXT("%d"),PosPage);
                        SetWindowText(hEditPage,szTextBuf);
                        SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    }
                    break;
                //PageBegin
                case 14:
                    PosPage=1;
                    sprintf(szTextBuf,TEXT("%d"),PosPage);
                    SetWindowText(hEditPage,szTextBuf);
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    break;
                //PageEnd
                case 15:
                    PosPage=TotalPage;
                    sprintf(szTextBuf,TEXT("%d"),PosPage);
                    SetWindowText(hEditPage,szTextBuf);
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    break;
                //页数编辑
                case 16:
                    GetWindowText(hEditPage,szTextBuf,100);
                    if (strlen(szTextBuf)==0) break;
                    vis_Page=true;
                    if (szTextBuf[0]=='0') vis_Page=false;
                    for (i=0;i<strlen(szTextBuf);i++)
                        if (szTextBuf[i]<48 || szTextBuf[i]>57)
                        {
                            vis_Page=false;
                            break;
                        }
                    if (vis_Page)
                    {
                        EditPage=atof(szTextBuf);
                        if (EditPage>0 && EditPage<=TotalPage)
                        {
                            PreviousPage=PosPage;
                            PosPage=EditPage;
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                        }
                        //超过页数范围，修改为原来页数
                        else
                        {
                            sprintf(szTextBuf,TEXT("%d"),PreviousPage);
                            SetWindowText(hEditPage,szTextBuf);
                        }
                    }
                    //有特殊符号，修改为原来页数
                    else
                    {
                            sprintf(szTextBuf,TEXT("%d"),PreviousPage);
                            SetWindowText(hEditPage,szTextBuf);
                    }
                    break;

                //点击深度查看电影按钮
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                    PosMovie=ShowMovie[(PosPage-1)*10+wParam-18];
                    total_history++;
                    for (i=total_history-1;i>=1;i--)
                        strcpy(history[i],history[i-1]);
                    GetLocalTime(&sys);
                    sprintf(history[0],TEXT("%s %4d/%02d/%02d %02d:%02d:%02d 星期%s\n"),movie[PosMovie].Name,sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,weekname[sys.wDayOfWeek]);
/*
                    strcpy(szCategory,"");
                    for (i=1;i<10;i++)
                        if (movie[PosMovie].Category[i]==1)
                        {
                            strcat(szCategory,CategoryName[i]);
                            strcat(szCategory," ");
                        }
                    sprintf(szTextBuf,TEXT("电影名称:%s\r\n类别:%s\r\n总体评分:%.1f\r\n上映时间:%d-%d-%d\r\n制片国家/地区:%s"),movie[PosMovie].Name,szCategory,movie[PosMovie].OverallMark,movie[PosMovie].year,movie[PosMovie].month,movie[PosMovie].day,movie[PosMovie].Place);
                    MessageBox(hWnd,szTextBuf,TEXT("电影信息"),MB_OK);
*/
                    fileclose_movie_introduce(PosMovie);
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,"Movie_Modify\\bin\\Debug\\Movie_Modify.exe");
                    system(szTextBuf);
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    break;

                //细分模式
                case 28:
                case 29:
                case 30:
                case 31:
                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                    switch(ShowMode)
                    {
                        //电影类别
                        case 2:
                            TotalMovie=0;
                            for (i=0;i<total_movie;i++)
                                if (movie[i].Category[wParam-27]==1)
                                {
                                    ShowMovie[TotalMovie]=i;
                                    TotalMovie++;
                                }
                            break;
                        //适合心情
                        case 3:
                            TotalMovie=0;
                            for (i=0;i<total_movie;i++)
                                if (movie[i].Mood==(wParam-27))
                                {
                                    ShowMovie[TotalMovie]=i;
                                    TotalMovie++;
                                }
                            break;
                        //用户状态
                        case 4:
                            TotalMovie=0;
                            for (i=0;i<total_movie;i++)
                                if (movie[i].Condition==(wParam-27))
                                {
                                    ShowMovie[TotalMovie]=i;
                                    TotalMovie++;
                                }
                            break;
                        default:
                            return DefWindowProc(hWnd,message,wParam,lParam);
                    }
                    TotalPage=TotalMovie/10;
                    if (TotalMovie%10!=0) TotalPage++;
                    PosPage=1;
                    sprintf(szTextBuf,TEXT("总有%d页"),TotalPage);
                    SetWindowText(hLabTotalPage,szTextBuf);
                    sprintf(szTextBuf,TEXT("%d"),PosPage);
                    SetWindowText(hEditPage,szTextBuf);
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)100,NULL);
                    break;
                //显示电影页面信息
                case 100:
                    for (i=0;i<mins(TotalMovie-PosPage*10+10,10);i++)
                    {
                        strcpy(szTextBuf,filename);
                        strcat(szTextBuf,movie[ShowMovie[(PosPage-1)*10+i]].Photo);
                        //图片显示
                        hdc=GetDC(hWnd);
                        //创建矩形覆盖原有图片
                        Rectangle(hdc,130+(i%5)*170,125+(i/5)*270,260+(i%5)*170,295+(i/5)*270);
                        hdc=GetDC(hWnd);
                        mdc=CreateCompatibleDC(hdc);
                        bg=(HBITMAP)LoadImage(
                            NULL,
                            szTextBuf,
                            IMAGE_BITMAP,120,160,LR_LOADFROMFILE
                        );
                        SelectObject(mdc,bg);
                        BitBlt(hdc,135+(i%5)*170,130+(i/5)*270,120,160,mdc,0,0,SRCAND);
                        //电影信息
                        ShowWindow(hEditMovieShow[i],SW_SHOW);
                        ShowWindow(hBtnInformationShow[i],SW_SHOW);
                        SetWindowText(hEditMovieShow[i],movie[ShowMovie[(PosPage-1)*10+i]].Name);
                        switch(ShowMode)
                        {
                            case 5:
                                if (movie[ShowMovie[(PosPage-1)*10+i]].month<10 && movie[ShowMovie[(PosPage-1)*10+i]].day<10)
                                    sprintf(szTextBuf,TEXT("%d-0%d-0%d"),movie[ShowMovie[(PosPage-1)*10+i]].year,movie[ShowMovie[(PosPage-1)*10+i]].month,movie[ShowMovie[(PosPage-1)*10+i]].day);
                                else if (movie[ShowMovie[(PosPage-1)*10+i]].month<10 && movie[ShowMovie[(PosPage-1)*10+i]].day>=10)
                                    sprintf(szTextBuf,TEXT("%d-0%d-%d"),movie[ShowMovie[(PosPage-1)*10+i]].year,movie[ShowMovie[(PosPage-1)*10+i]].month,movie[ShowMovie[(PosPage-1)*10+i]].day);
                                else if (movie[ShowMovie[(PosPage-1)*10+i]].month>=10 && movie[ShowMovie[(PosPage-1)*10+i]].day<10)
                                    sprintf(szTextBuf,TEXT("%d-%d-0%d"),movie[ShowMovie[(PosPage-1)*10+i]].year,movie[ShowMovie[(PosPage-1)*10+i]].month,movie[ShowMovie[(PosPage-1)*10+i]].day);
                                else if (movie[ShowMovie[(PosPage-1)*10+i]].month>=10 && movie[ShowMovie[(PosPage-1)*10+i]].day>=10)
                                    sprintf(szTextBuf,TEXT("%d-%d-%d"),movie[ShowMovie[(PosPage-1)*10+i]].year,movie[ShowMovie[(PosPage-1)*10+i]].month,movie[ShowMovie[(PosPage-1)*10+i]].day);
                                break;
                            //专家评分
                            case 7:
                                sprintf(szTextBuf,TEXT("%.1f"),movie[ShowMovie[(PosPage-1)*10+i]].ProfessorMark);
                                break;
                            //总体评分和其它显示方式
                            default:
                                sprintf(szTextBuf,TEXT("%.1f"),movie[ShowMovie[(PosPage-1)*10+i]].OverallMark);
                                break;
                        }
                        SetWindowText(hBtnInformationShow[i],szTextBuf);
                    }
                    for (i=TotalMovie-PosPage*10+10;i<10;i++)
                    {
                        ShowWindow(hEditMovieShow[i],SW_HIDE);
                        ShowWindow(hBtnInformationShow[i],SW_HIDE);
                        SelectObject(hdc,hPenWhite);
                        Rectangle(hdc,130+(i%5)*170,125+(i/5)*270,260+(i%5)*170,295+(i/5)*270);
                    }
                    break;

                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }

            break;

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            switch(wParam)
            {
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                    hdc=GetDC(hWnd);
                    //选择白笔消除
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,30,50+DrawPrevious*40,NULL);
                    LineTo(hdc,30,80+DrawPrevious*40);
                    LineTo(hdc,110,80+DrawPrevious*40);
                    LineTo(hdc,110,50+DrawPrevious*40);
                    LineTo(hdc,30,50+DrawPrevious*40);
                    //选择红笔
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,30,50+DrawCurrent*40,NULL);
                    LineTo(hdc,30,80+DrawCurrent*40);
                    LineTo(hdc,110,80+DrawCurrent*40);
                    LineTo(hdc,110,50+DrawCurrent*40);
                    LineTo(hdc,30,50+DrawCurrent*40);
                    break;
            }
            EndPaint(hWnd,&ps);
            break;

        case WM_TIMER:
            SetWindowText(hEditIntroduce,introduce[PosIntroduce]);
            PosIntroduce=(PosIntroduce+1)%total_introduce;
            break;

        case WM_DESTROY:
            fileclose_history();
            fileclose_user();
            DeleteObject(hFont);
            DeleteObject(hPenRed);
            DeleteObject(hPenWhite);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}

long mins(long a,long b)
{
    if (a>b)
        return b;
    else
        return a;
}
