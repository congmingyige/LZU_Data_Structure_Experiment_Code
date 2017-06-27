#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

HDC hdc,mdc;
HBITMAP bg;

struct movie movie[1000];
struct user user[1000];
long total_movie,pos_movie;
long total_user,pos_user,CurrentUser;
char filename[100];

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    //读入电影信息
    fileopen_movie();
    //模式 修改电影/查看电影
    fileopen_movie_introduce();

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
        TEXT("电影后台管理"),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        300,  //初始化时x轴的位置
        5,  //初始化时y轴的位置
        825,  //窗口宽度
        825,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );

    //显示窗口
    ShowWindow(hwnd,iCmdShow);
    //更新（绘制）窗口
    UpdateWindow(hwnd);

//初始化
    //获得文件路径
    GetModuleFileName(NULL,filename,100);
    *(strstr(filename,"MovieSoftware")+14)='\0';
    //电影编号从0开始 处于新建状态,则新建的电影编号等同于电影总数
    pos_movie=total_movie;
    if (ModeInterface==0)
        //修改电影 新建 清空
        SendMessage(hwnd,WM_COMMAND,(WPARAM)48,NULL);
    else
        //查看电影 跳转页码
        SendMessage(hwnd,WM_COMMAND,(WPARAM)1000,NULL);

    /**********第③步：消息循环**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage(&msg);  //分派消息
        switch(msg.message)
        {
            case WM_KEYDOWN:
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('1')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)48,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('2')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)50,NULL);
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
    RECT rect;

    static bool vis_edit=true,vis_page=true,vis_check=true,vis_create=true;
    long i,page;
    //0:新建 1:修改
    static int EditMode=0;
    static int DrawPrevious,DrawCurrent=1;
    char s[100],s1[100];

    static HPEN hPenRed;
    static HPEN hPenWhite;

    static HFONT hFont;
    static HFONT hFontTitle;
    static HFONT hFontNumber;
//电影名
    static HWND hLabMovieName;
    static HWND hEditMovieName;
//电影类别
    static HWND hLabMovieMode;
    static HWND checkboxComedy;
    static HWND checkboxRomance;
    static HWND checkboxAction;
    static HWND checkboxCartoon;
    static HWND checkboxTeen;
    static HWND checkboxFeature;
    static HWND checkboxSci_Fic;
    static HWND checkboxThriller;
    static HWND checkboxOther;
//适合人群
    static HWND hLabMoviePeople;
    //心情
    static HWND radioSad;
    static HWND radioDisappointed;
    static HWND radioRegret;
    static HWND radioNervious;
    //状态
    static HWND radio1;
    static HWND radio2;
    static HWND radio3;
    static HWND radio4;
    //性别
    static HWND radioBoy;
    static HWND radioGirl;
    //年龄
    static HWND radioChild;
    static HWND radioTeen;
    static HWND radioMiddleAge;
    static HWND radioOld;
//评分
    static HWND hLabOverallMark;
    static HWND hEditOverallMark;
    static HWND hLabProfessorMark;
    static HWND hEditProfessorMark;
    static HWND hLabUserMark;
    static HWND hEditUserMark;
    static HWND hLabMarkStandard;
    static HWND hBtnMarkStandard;
    //上映时间和地点
    static HWND hLabTime;
    static HWND hEditTime;
    static HWND hLabPlace;
    static HWND hEditPlace;
    //电影简介
    static HWND hEditIntroduce;
    //输入图片、种子、电影 电脑地址
    static HWND hLabPhotoAddress;
    static HWND hEditPhotoAddress;
    static HWND hLabTorrentAddress;
    static HWND hEditTorrentAddress;
    static HWND hLabFileAddress;
    static HWND hEditFileAddress;
    //确认按钮
    static HWND hBtnModifySubmit;
    //新建电影、查看电影按钮
    static HWND hBtnNewMovie;
    static HWND hBtnCheckMovie;
    static HWND hEditCheckMovie;
    //电影信息
    static HWND hBtnMovieInformation;
    //保存并退出按钮
    static HWND hBtnSaveAndExit;

    //字符串,用于输入
    TCHAR szTextBuf[100],szNumBuf[100],szPassage[1000];

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

            //电影名
            hLabMovieName=CreateWindow(
                TEXT("static"),TEXT("电影名:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,40,120,40,
                hWnd,(HMENU)1,hInst,NULL
            );

            hEditMovieName=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                240,40,345,40,
                hWnd,(HMENU)2,hInst,NULL
            );
            //电影类别
            hLabMovieMode=CreateWindow(
                TEXT("static"),TEXT("电影类别:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,100,120,40,
                hWnd,(HMENU)3,hInst,NULL
            );

            checkboxComedy=CreateWindow(
                TEXT("button"),TEXT("喜剧"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                215,92,65,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            checkboxRomance=CreateWindow(
                TEXT("button"),TEXT("爱情"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                285,92,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            checkboxAction=CreateWindow(
                TEXT("button"),TEXT("动作"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                355,92,65,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            checkboxCartoon=CreateWindow(
                TEXT("button"),TEXT("动画"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                425,92,65,26,
                hWnd,(HMENU)7,hInst,NULL
            );

            checkboxTeen=CreateWindow(
                TEXT("button"),TEXT("剧情"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                495,92,65,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            checkboxFeature=CreateWindow(
                TEXT("button"),TEXT("悬疑"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                215,122,65,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            checkboxSci_Fic=CreateWindow(
                TEXT("button"),TEXT("科幻"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                285,122,65,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            checkboxThriller=CreateWindow(
                TEXT("button"),TEXT("冒险"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                355,122,65,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            checkboxOther=CreateWindow(
                TEXT("button"),TEXT("犯罪/战争"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                425,122,110,26,
                hWnd,(HMENU)12,hInst,NULL
            );
            //适合人群
            hLabMoviePeople=CreateWindow(
                TEXT("static"),TEXT("适合人群:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,166,120,40,
                hWnd,(HMENU)13,hInst,NULL
            );
            //心情
            radioSad=CreateWindow(
                TEXT("button"),TEXT("伤心"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                215,158,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            radioDisappointed=CreateWindow(
                TEXT("button"),TEXT("失望"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                285,158,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            radioRegret=CreateWindow(
                TEXT("button"),TEXT("后悔"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                355,158,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );

            radioNervious=CreateWindow(
                TEXT("button"),TEXT("紧张"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                425,158,65,26,
                hWnd,(HMENU)17,hInst,NULL
            );
            //状态
            radio1=CreateWindow(
                TEXT("button"),TEXT("临近考试"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                215,188,95,26,
                hWnd,(HMENU)18,hInst,NULL
            );

            radio2=CreateWindow(
                TEXT("button"),TEXT("身体恢复"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                315,188,95,26,
                hWnd,(HMENU)19,hInst,NULL
            );

            radio3=CreateWindow(
                TEXT("button"),TEXT("缺乏动力"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                415,188,95,26,
                hWnd,(HMENU)20,hInst,NULL
            );

            radio4=CreateWindow(
                TEXT("button"),TEXT("爱情受伤"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                515,188,95,26,
                hWnd,(HMENU)21,hInst,NULL
            );
            //性别
            radioBoy=CreateWindow(
                TEXT("button"),TEXT("男"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                215,218,45,26,
                hWnd,(HMENU)22,hInst,NULL
            );

            radioGirl=CreateWindow(
                TEXT("button"),TEXT("女"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                265,218,45,26,
                hWnd,(HMENU)23,hInst,NULL
            );
            //年龄
            radioChild=CreateWindow(
                TEXT("button"),TEXT("儿童"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                315,218,60,26,
                hWnd,(HMENU)24,hInst,NULL
            );

            radioTeen=CreateWindow(
                TEXT("button"),TEXT("青少年"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                380,218,80,26,
                hWnd,(HMENU)25,hInst,NULL
            );

            radioMiddleAge=CreateWindow(
                TEXT("button"),TEXT("中年人"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                465,218,80,26,
                hWnd,(HMENU)26,hInst,NULL
            );

            radioOld=CreateWindow(
                TEXT("button"),TEXT("老人"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                550,218,60,26,
                hWnd,(HMENU)27,hInst,NULL
            );

            //评分
            //总评
            hLabOverallMark=CreateWindow(
                TEXT("static"),TEXT("总体评分:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,255,120,40,
                hWnd,(HMENU)28,hInst,NULL
            );
            //总评一定会有
            hEditOverallMark=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                215,255,55,40,
                hWnd,(HMENU)29,hInst,NULL
            );

            //专家评分
            hLabProfessorMark=CreateWindow(
                TEXT("static"),TEXT("专家评分:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                280,255,120,40,
                hWnd,(HMENU)30,hInst,NULL
            );
            //专家一定要评分
            hEditProfessorMark=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                405,255,55,40,
                hWnd,(HMENU)31,hInst,NULL
            );

            //用户评分
            hLabUserMark=CreateWindow(
                TEXT("static"),TEXT("用户评分:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                470,255,120,40,
                hWnd,(HMENU)32,hInst,NULL
            );

            hEditUserMark=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY,
                595,255,155,40,
                hWnd,(HMENU)33,hInst,NULL
            );

            sprintf(szTextBuf,TEXT("分数:0.1~9.9,专家评分%d%%,用户评分%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
            hLabMarkStandard=CreateWindow(
                TEXT("static"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                140,305,450,40,
                hWnd,(HMENU)34,hInst,NULL
            );

            hBtnMarkStandard=CreateWindow(
                TEXT("button"),TEXT("评分规则"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                620,305,80,40,
                hWnd,(HMENU)35,hInst,NULL
            );

            hLabTime=CreateWindow(
                TEXT("static"),TEXT("中国上映时间:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,355,150,40,
                hWnd,(HMENU)36,hInst,NULL
            );

            hEditTime=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                245,355,150,40,
                hWnd,(HMENU)37,hInst,NULL
            );

            hLabPlace=CreateWindow(
                TEXT("static"),TEXT("制片国家/地址:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                405,355,170,40,
                hWnd,(HMENU)38,hInst,NULL
            );

            hEditPlace=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                580,355,170,40,
                hWnd,(HMENU)39,hInst,NULL
            );
            //电影简介
            hEditIntroduce=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                90,405,660,170,
                hWnd,(HMENU)40,hInst,NULL
            );

            //输入图片 电脑地址
            hLabPhotoAddress=CreateWindow(
                TEXT("static"),TEXT("图片地址:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,585,120,40,
                hWnd,(HMENU)41,hInst,NULL
            );

            hEditPhotoAddress=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,585,510,40,
                hWnd,(HMENU)42,hInst,NULL
            );
            //输入种子 电脑地址
            hLabTorrentAddress=CreateWindow(
                TEXT("static"),TEXT("种子地址:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,635,120,40,
                hWnd,(HMENU)43,hInst,NULL
            );

            hEditTorrentAddress=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,635,510,40,
                hWnd,(HMENU)44,hInst,NULL
            );
            //输入视频 电脑地址
            hLabFileAddress=CreateWindow(
                TEXT("static"),TEXT("视频地址:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,685,120,40,
                hWnd,(HMENU)45,hInst,NULL
            );

            hEditFileAddress=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,685,510,40,
                hWnd,(HMENU)46,hInst,NULL
            );

            hBtnModifySubmit=CreateWindow(
                TEXT("button"),TEXT("确认"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                300,735,80,40,
                hWnd,(HMENU)47,hInst,NULL
            );

            hBtnNewMovie=CreateWindow(
                TEXT("button"),TEXT("新建电影"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                280,5,100,30,
                hWnd,(HMENU)48,hInst,NULL
            );

            hBtnCheckMovie=CreateWindow(
                TEXT("button"),TEXT("修改电影"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                390,5,100,30,
                hWnd,(HMENU)49,hInst,NULL
            );

            hEditCheckMovie=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                500,5,50,30,
                hWnd,(HMENU)50,hInst,NULL
            );

            hBtnMovieInformation=CreateWindow(
                TEXT("button"),TEXT("电影信息"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                100,5,100,30,
                hWnd,(HMENU)51,hInst,NULL
            );

            hBtnSaveAndExit=CreateWindow(
                TEXT("button"),TEXT("保存并退出"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                390,735,100,40,
                hWnd,(HMENU)52,hInst,NULL
            );

            //电影名
            SendMessage(hLabMovieName,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditMovieName,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            //电影类别
            SendMessage(hLabMovieMode,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(checkboxComedy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxRomance,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAction,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxCartoon,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxTeen,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxFeature,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxSci_Fic,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxThriller,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxOther,WM_SETFONT,(WPARAM)hFont,NULL);
            //适合人群
            SendMessage(hLabMoviePeople,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            //心情
            SendMessage(radioSad,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioDisappointed,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioRegret,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioNervious,WM_SETFONT,(WPARAM)hFont,NULL);
            //状态
            SendMessage(radio1,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radio2,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radio3,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radio4,WM_SETFONT,(WPARAM)hFont,NULL);
            //性别
            SendMessage(radioBoy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioGirl,WM_SETFONT,(WPARAM)hFont,NULL);
            //年龄
            SendMessage(radioChild,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioTeen,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioMiddleAge,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioOld,WM_SETFONT,(WPARAM)hFont,NULL);
            //评分
            SendMessage(hLabOverallMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditOverallMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabProfessorMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditProfessorMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabUserMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditUserMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabMarkStandard,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMarkStandard,WM_SETFONT,(WPARAM)hFont,NULL);
            //上映时间和地点
            SendMessage(hLabTime,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditTime,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabPlace,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditPlace,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            //电影简介
            SendMessage(hEditIntroduce,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            //输入图片、种子、电影 电脑地址
            SendMessage(hLabPhotoAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditPhotoAddress,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabTorrentAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditTorrentAddress,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabFileAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditFileAddress,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            //确认按钮
            SendMessage(hBtnModifySubmit,WM_SETFONT,(WPARAM)hFont,NULL);
            //新建电影、查看电影按钮
            SendMessage(hBtnNewMovie,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnCheckMovie,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditCheckMovie,WM_SETFONT,(WPARAM)hFont,NULL);
            //电影信息
            SendMessage(hBtnMovieInformation,WM_SETFONT,(WPARAM)hFont,NULL);
            //保存并退出按钮
            SendMessage(hBtnSaveAndExit,WM_SETFONT,(WPARAM)hFont,NULL);

            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch (wmId)
            {
                case 1000:
                    sprintf(szTextBuf,TEXT("%d"),ModeNumber+1);
                    SetWindowText(hEditCheckMovie,szTextBuf);
                    ShowWindow(hBtnNewMovie,SW_HIDE);
                    ShowWindow(hBtnCheckMovie,SW_HIDE);
                    ShowWindow(hEditCheckMovie,SW_HIDE);
                    ShowWindow(hBtnModifySubmit,SW_HIDE);
                    ShowWindow(hBtnSaveAndExit,SW_HIDE);
                    ShowWindow(hBtnMovieInformation,SW_HIDE);
                    break;
                //电影名 若为查找状态 若书写的文字与已有的电影名相同则填入信息
                case 2:
                    GetWindowText(hEditCheckMovie,szTextBuf,100);
                    if (strlen(szTextBuf)==0 && EditMode==1)
                    {
                        vis_check=false;
                        vis_edit=false;
                        GetWindowText(hEditMovieName,szTextBuf,100);
                        for (i=0;i<total_movie;i++)
                            if (strcmp(movie[i].Name,szTextBuf)==0)
                            {
                                vis_edit=true;
                                break;
                            }
                        //如果找不到相同名字的电影就清空屏幕
                        if (!vis_edit)
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                        //如果找到就填入数据
                        else
                        {
                            vis_create=true;
                            pos_movie=i;
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)102,NULL);
                        }
                    }
                    //判断电影名是否已经被使用
                    vis_edit=false;
                    GetWindowText(hEditMovieName,szTextBuf,100);
                    for (i=0;i<total_movie;i++)
                        if (i!=pos_movie && strcmp(movie[i].Name,szTextBuf)==0)
                        {
                            vis_edit=true;
                            break;
                        }
                    if (vis_edit)
                    {
                        rect.left=510;
                        rect.right=800;
                        rect.top=730;
                        rect.bottom=780;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        DrawText(
                            hdc,
                            TEXT("电影名称已被使用"),
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    else
                    {
                        rect.left=510;
                        rect.right=800;
                        rect.top=730;
                        rect.bottom=780;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        for (i=0;i<strlen("电影名称已被使用");i++) szTextBuf[i]=' ';
                        szTextBuf[i]='\0';
                        DrawText(
                            hdc,
                            szTextBuf,
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    break;

                //改变专家评分
                case 31:
                    GetWindowText(hEditProfessorMark,szTextBuf,100);
                    if (strlen(szTextBuf)==3 && szTextBuf[1]=='.' && szTextBuf[0]>='0' && szTextBuf[0]<='9' && szTextBuf[2]>='0' && szTextBuf[2]<='9')
                    {
                        movie[pos_movie].ProfessorMark=(szTextBuf[0]-48.0)+(szTextBuf[2]-48.0)/10.0;
                        //获得专家评分、用户评分占总评的比例
                        if (movie[pos_movie].UserNumber<5) movie[pos_movie].RatioMark=1.0;
                            else if (movie[pos_movie].UserNumber<=100) movie[pos_movie].RatioMark=0.7;
                                else if (movie[pos_movie].UserNumber<=1000) movie[pos_movie].RatioMark=0.5;
                                    else movie[pos_movie].RatioMark=0.3;
                        //计算总评分数
                        if (movie[pos_movie].UserNumber==0)
                            movie[pos_movie].OverallMark=movie[pos_movie].ProfessorMark;
                        else
                            movie[pos_movie].OverallMark=movie[pos_movie].ProfessorMark*movie[pos_movie].RatioMark+movie[pos_movie].UserMark/movie[pos_movie].UserNumber*(1-movie[pos_movie].RatioMark);
                        //输出总评分数
                        sprintf(szNumBuf,TEXT("%.1f"),movie[pos_movie].OverallMark);
                        SetWindowText(hEditOverallMark,szNumBuf);
                        //输出专家评分、用户评分占总评的比例
                        sprintf(szTextBuf,TEXT("分数:0.1~9.9,专家评分%d%%,用户评分%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                        SetWindowText(hLabMarkStandard,szTextBuf);
                    }
                    break;

                //评分规则
                case 35:
                    wsprintf(szTextBuf,TEXT("用户评分人数：\r\n <5\t\t\t专家100%% 用户0%% \r\n 5~100\t\t\t专家70%% 用户30%% \r\n 101~1000\t\t专家50%% 用户50%% \r\n >1001\t\t\t专家30%% 用户70%%"));
                    MessageBox(hWnd,szTextBuf,TEXT("评分规则"),MB_ICONINFORMATION);
                    break;

                //电影简介
                case 40:
                    GetWindowText(hEditIntroduce,szPassage,1000);
                    if (strlen(szPassage)==0)
                    {
                        rect.left=0;
                        rect.right=290;
                        rect.top=730;
                        rect.bottom=780;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        DrawText(
                            hdc,
                            TEXT("请修改电影简介"),
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    else
                    {
                        rect.left=0;
                        rect.right=290;
                        rect.top=730;
                        rect.bottom=780;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        for (i=0;i<strlen("请修改电影简介");i++)
                            szPassage[i]=' ';
                        szPassage[i]='\0';
                        DrawText(
                            hdc,
                            szPassage,
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    break;

                //图片地址
                case 42:
                    SendMessage(hWnd,WM_PAINT,(WPARAM)42,NULL);
                    break;
                //确认按钮
                case 47:
                    //判断是否处于新建状态
                    if (!vis_create)
                    {
                        MessageBox(hWnd,TEXT("电影处于修改状态而非新建窗台"),TEXT("提醒"),MB_OK);
                        break;
                    }
                    GetWindowText(hEditMovieName,szTextBuf,100);
                    //电影
                    if (strlen(szTextBuf)==0)
                    {
                        MessageBox(hWnd,TEXT("电影名称不能为空"),TEXT("提醒"),MB_OK);
                        break;
                    }
                    vis_edit=true;
                    for (i=0;i<total_movie;i++)
                        if (i!=pos_movie && strcmp(szTextBuf,movie[i].Name)==0)
                        {
                            vis_edit=false;
                            break;
                        }
                    if (!vis_edit)
                    {
                        MessageBox(hWnd,TEXT("电影名称已被使用"),TEXT("提醒"),MB_OK);
                        break;
                    }
                    //专家评分
                    GetWindowText(hEditProfessorMark,szTextBuf,100);
                    if (strlen(szTextBuf)==0)
                    {
                        MessageBox(hWnd,TEXT("专家评分未填写"),TEXT("提醒"),MB_OK);
                        break;
                    }
                    if (!(strlen(szTextBuf)==3 && szTextBuf[1]=='.' && szTextBuf[0]>='0' && szTextBuf[0]<='9' && szTextBuf[2]>='0' && szTextBuf[2]<='9'))
                    {
                        MessageBox(hWnd,TEXT("专家评分填写错误"),TEXT("提醒"),MB_OK);
                        break;
                    }
                    //上映时间
                    GetWindowText(hEditTime,szTextBuf,100);
                    if (strlen(szTextBuf)==0)
                    {
                        MessageBox(hWnd,TEXT("上映时间不能为空"),TEXT("提醒"),MB_OK);
                        break;
                    }
                    vis_edit=true;
                    for (i=0;i<10;i++)
                        if (i!=4 && i!=7 && (szTextBuf[i]<'0' || szTextBuf[i]>'9'))
                        {
                            vis_edit=false;
                            break;
                        }
                    if (vis_edit==false || strlen(szTextBuf)!=10 || szTextBuf[4]!='-' || szTextBuf[7]!='-')
                    {
                        MessageBox(hWnd,TEXT("上映时间填写错误"),TEXT("提醒"),MB_OK);
                        break;
                    }
                    //当电影确认创建时要 total_movie++;
                    if (pos_movie==total_movie) total_movie++;
                    //时间example 2008-01-01
                    GetWindowText(hEditTime,szTextBuf,100);
                    strcpy(s1,szTextBuf);
                    strncpy(s,s1,4);
                    s[4]='\0';
                    movie[pos_movie].year=atoi(s);
                    strncpy(s,s1+5,2);
                    s[2]='\0';
                    movie[pos_movie].month=atoi(s);
                    strncpy(s,s1+8,2);
                    s[2]='\0';
                    movie[pos_movie].day=atoi(s);
                    //文字
                    GetWindowText(hEditMovieName,movie[pos_movie].Name,100);
                    GetWindowText(hEditPlace,movie[pos_movie].Place,100);
                    GetWindowText(hEditIntroduce,movie[pos_movie].Passage,1000);
                    GetWindowText(hEditPhotoAddress,movie[pos_movie].Photo,100);
                    GetWindowText(hEditTorrentAddress,movie[pos_movie].Torrent,100);
                    GetWindowText(hEditFileAddress,movie[pos_movie].File,100);
                    //电影类别
                    for (i=1;i<10;i++)
                        if (IsDlgButtonChecked(hWnd,3+i)==BST_CHECKED) movie[pos_movie].Category[i]=1;
                            else movie[pos_movie].Category[i]=0;
                    //心情、状态、性别、年龄
                    for (i=14;i<=17;i++)
                        if (IsDlgButtonChecked(hWnd,i)==BST_CHECKED)
                        {
                            movie[pos_movie].Mood=i-13;
                            break;
                        }
                    for (i=18;i<=21;i++)
                        if (IsDlgButtonChecked(hWnd,i)==BST_CHECKED)
                        {
                            movie[pos_movie].Condition=i-17;
                            break;
                        }
                    for (i=22;i<=23;i++)
                        if (IsDlgButtonChecked(hWnd,i)==BST_CHECKED)
                        {
                            movie[pos_movie].Sex=i-21;
                            break;
                        }
                    for (i=24;i<=27;i++)
                        if (IsDlgButtonChecked(hWnd,i)==BST_CHECKED)
                        {
                            movie[pos_movie].Age=i-23;
                            break;
                        }
                    //总体评分、专家评分随着修改而更改，
                    //而用户总评分和用户评价人数不会变，所以这里不用操作
                    MessageBox(hWnd,TEXT("修改成功"),TEXT("提醒"),NULL);
                    break;
                //新建 清空
                case 48:
                    vis_create=true;
                    //更新矩形
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=0;
                    if (DrawPrevious!=DrawCurrent)
                        SendMessage(hWnd,WM_PAINT,(WPARAM)DrawCurrent,NULL);
                    EditMode=0;
                    //清空页面
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                    //电影编号从0开始，所以新建的电影编号为total_movie
                    pos_movie=total_movie;
                    movie[pos_movie].Number=pos_movie;
                    movie[pos_movie].RatioMark=1.0;
                    movie[pos_movie].UserNumber=0;
                    movie[pos_movie].OverallMark=0;
                    movie[pos_movie].ProfessorMark=0;
                    movie[pos_movie].UserMark=0;
                    movie[pos_movie].Mood=0;
                    movie[pos_movie].Sex=0;
                    movie[pos_movie].Age=0;
                    movie[pos_movie].Condition=0;
                    for (i=1;i<=9;i++) movie[pos_movie].Category[i]=0;
                    SetWindowText(hEditMovieName,"");
                    break;
                //修改电影按钮
                case 49:
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=1;
                    if (DrawPrevious!=DrawCurrent)
                        SendMessage(hWnd,WM_PAINT,(WPARAM)DrawCurrent,NULL);
                    EditMode=1;
                    SetWindowText(hEditCheckMovie,"");
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                    break;

                //跳转 修改电影
                case 50:
                    vis_create=true;
                    //更新矩形
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=1;
                    if (DrawPrevious!=DrawCurrent)
                        SendMessage(hWnd,WM_PAINT,(WPARAM)DrawCurrent,NULL);
                    EditMode=1;
                    GetWindowText(hEditCheckMovie,szTextBuf,100);
                    if (strlen(szTextBuf)==0)
                    {
                        SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                        vis_create=false;
                        break;
                    }
                    vis_page=true;
                    if (szTextBuf[0]=='0') vis_page=false;
                    for (i=0;i<strlen(szTextBuf);i++)
                        if (szTextBuf[i]<48 || szTextBuf[i]>57)
                        {
                            vis_page=false;
                            break;
                        }
                    if (vis_page)
                    {
                        page=atoi(szTextBuf);
                        if (page<=total_movie)
                        {
                            vis_create=true;
                            pos_movie=page-1;
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)102,NULL);
                        }
                        else
                        {
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                            vis_create=false;
                        }
                    }
                    break;
                //电影信息
                case 51:
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,"movie.txt");
                    system(szTextBuf);
                    break;
                //保存并退出按钮
                case 52:
                    fileclose_movie();
                    SendMessage(hWnd,WM_DESTROY,NULL,NULL);
                    break;
                //清空窗口
                case 101:
                        //如果为新建电影状态
                    if (vis_check) SetWindowText(hEditMovieName,"");
                        //如果为修改电影且页数编辑框为空时 就不要修改电影名称了
                    else vis_edit=true;
                    //电影简介 提示行
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)40,NULL);
                    SetWindowText(hEditTime,"");
                    SetWindowText(hEditPlace,"");
                    SetWindowText(hEditIntroduce,"");
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,"Photo\\");
                    SetWindowText(hEditPhotoAddress,szTextBuf);
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,"Torrent\\");
                    SetWindowText(hEditTorrentAddress,szTextBuf);
                    SetWindowText(hEditFileAddress,"");
                    //分数
                    SetWindowText(hEditOverallMark,"");
                    SetWindowText(hEditProfessorMark,"");
                    SetWindowText(hEditUserMark,"0/0人");
                    SetWindowText(hLabMarkStandard,"分数:0.1~9.9,专家评分100%,用户评分0%");
                    //清空电影类别
                    for (i=1;i<10;i++)
                        CheckDlgButton(hWnd,3+i,BST_UNCHECKED);
                    //清空心情、状态、性别、年龄
                    CheckRadioButton(hWnd,14,17,NULL);
                    CheckRadioButton(hWnd,18,21,NULL);
                    CheckRadioButton(hWnd,22,23,NULL);
                    CheckRadioButton(hWnd,24,27,NULL);
                    //创建矩形，覆盖图片
                    hdc=GetDC(hWnd);
                    if (ModeInterface==0)
                        Rectangle(hdc,610,40,740,210);
                    break;

                //填写窗口
                case 102:
                        //如果属于通过页数跳转电影状态
                    if (vis_check) SetWindowText(hEditMovieName,movie[pos_movie].Name);
                        //如果为修改电影且页数编辑框为空时 就不要修改电影名称了
                    else vis_check=true;
                    //电影简介 提示行
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)40,NULL);
                    if (movie[pos_movie].month<10 && movie[pos_movie].day<10)
                        sprintf(szTextBuf,TEXT("%d-0%d-0%d"),movie[pos_movie].year,movie[pos_movie].month,movie[pos_movie].day);
                    else if (movie[pos_movie].month<10 && movie[pos_movie].day>=10)
                        sprintf(szTextBuf,TEXT("%d-0%d-%d"),movie[pos_movie].year,movie[pos_movie].month,movie[pos_movie].day);
                    else if (movie[pos_movie].month>=10 && movie[pos_movie].day<10)
                        sprintf(szTextBuf,TEXT("%d-%d-0%d"),movie[pos_movie].year,movie[pos_movie].month,movie[pos_movie].day);
                    else if (movie[pos_movie].month>=10 && movie[pos_movie].day>=10)
                        sprintf(szTextBuf,TEXT("%d-%d-%d"),movie[pos_movie].year,movie[pos_movie].month,movie[pos_movie].day);
                    SetWindowText(hEditTime,szTextBuf);
                    SetWindowText(hEditPlace,movie[pos_movie].Place);
                    SetWindowText(hEditIntroduce,movie[pos_movie].Passage);
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,movie[pos_movie].Photo);
                    SetWindowText(hEditPhotoAddress,szTextBuf);
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,movie[pos_movie].Torrent);
                    SetWindowText(hEditTorrentAddress,szTextBuf);
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,movie[pos_movie].File);
                    SetWindowText(hEditFileAddress,szTextBuf);
                    //分数
                    sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].OverallMark);
                    SetWindowText(hEditOverallMark,szTextBuf);
                    sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].ProfessorMark);
                    SetWindowText(hEditProfessorMark,szTextBuf);
                    if (movie[pos_movie].UserNumber==0)
                        sprintf(szTextBuf,"0/0人");
                    else
                        sprintf(szTextBuf,TEXT("%.1f/%d人"),movie[pos_movie].UserMark/movie[pos_movie].UserNumber,movie[pos_movie].UserNumber);
                    SetWindowText(hEditUserMark,szTextBuf);
                    sprintf(szTextBuf,TEXT("分数:0.1~9.9,专家评分%d%%,用户评分%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                    SetWindowText(hLabMarkStandard,szTextBuf);
                    //显示电影类别
                    for (i=1;i<10;i++)
                        if (movie[pos_movie].Category[i]==1)
                            CheckDlgButton(hWnd,3+i,BST_CHECKED);
                        else CheckDlgButton(hWnd,3+i,BST_UNCHECKED);
                    //显示心情、状态、性别、年龄
                    if (movie[pos_movie].Mood!=-1)
                        CheckRadioButton(hWnd,14,17,13+movie[pos_movie].Mood);
                    if (movie[pos_movie].Condition!=-1)
                        CheckRadioButton(hWnd,18,21,17+movie[pos_movie].Condition);
                    if (movie[pos_movie].Sex!=-1)
                        CheckRadioButton(hWnd,22,23,21+movie[pos_movie].Sex);
                    if (movie[pos_movie].Age!=-1)
                        CheckRadioButton(hWnd,24,27,23+movie[pos_movie].Age);
                    //显示 图片
                    SendMessage(hWnd,WM_PAINT,(WPARAM)42,NULL);
                    break;

                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }
            break;


        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            switch (wParam)
            {
                case 0:
                    if (ModeInterface==1) break;
                    hdc=GetDC(hWnd);
                    //选择白笔消除
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,390,5,NULL);
                    LineTo(hdc,390,35);
                    LineTo(hdc,490,35);
                    LineTo(hdc,490,5);
                    LineTo(hdc,390,5);
                    //选择红笔
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,280,5,NULL);
                    LineTo(hdc,280,35);
                    LineTo(hdc,380,35);
                    LineTo(hdc,380,5);
                    LineTo(hdc,280,5);
                    break;

                case 1:
                    if (ModeInterface==1) break;
                    hdc=GetDC(hWnd);
                    //选择白笔消除
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,280,5,NULL);
                    LineTo(hdc,280,35);
                    LineTo(hdc,380,35);
                    LineTo(hdc,380,5);
                    LineTo(hdc,280,5);
                    //选择红笔
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,390,5,NULL);
                    LineTo(hdc,390,35);
                    LineTo(hdc,490,35);
                    LineTo(hdc,490,5);
                    LineTo(hdc,390,5);
                    break;

                case 42:
                    //插入图片
                    hdc=GetDC(hWnd);
                    //创建矩形覆盖原有图片
                    Rectangle(hdc,610,40,740,210);
                    GetWindowText(hEditPhotoAddress,szTextBuf,100);
                    hdc=GetDC(hWnd);
                    mdc=CreateCompatibleDC(hdc);
                    bg=(HBITMAP)LoadImage(
                        NULL,
                        szTextBuf,
                        IMAGE_BITMAP,120,160,LR_LOADFROMFILE
                    );
                    SelectObject(mdc,bg);
                    BitBlt(hdc,615,45,120,160,mdc,0,0,SRCAND);
                    break;
            }
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            //最后修改回来
            fileclose_movie_introduce();
            DeleteObject(hFont);
            DeleteObject(hFontTitle);
            DeleteObject(hFontNumber);
            DeleteObject(hPenRed);
            DeleteObject(hPenWhite);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
