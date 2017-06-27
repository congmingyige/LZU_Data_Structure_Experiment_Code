#include <windows.h>
#include "define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

struct movie movie[1000];
struct user user[1000];
long pos_user=-1,total_user,total_movie;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    //读入
    fileopen_user();
    fileopen_user_information();

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
    hwnd = CreateWindow(
        szClassName,  //窗口类的名字
        TEXT("信息完善"),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        500/*CW_USEDEFAULT*/,  //初始化时x轴的位置
        250/*CW_USEDEFAULT*/,  //初始化时y轴的位置
        500,  //窗口宽度
        300,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );

    //显示窗口
    ShowWindow(hwnd,iCmdShow);
    //更新（绘制）窗口
    UpdateWindow(hwnd);

    /**********第③步：消息循环**********/
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage (&msg);  //分派消息
    }

    return msg.wParam;
}

/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR szTextBuf[100];
    int wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    static HFONT hFont;  //逻辑字体
    //单选 性别
    static HWND labSex;
    static HWND radioMale;
    static HWND radioFemale;
    //单选 定义
    static HWND labDefine;
    static HWND radioStudent;
    static HWND radioWorker;
    static HWND radioOther;
    //单选 年龄
    static HWND labAge;
    static HWND radioChild;
    static HWND radioTeen;
    static HWND radioMiddleAge;
    static HWND radioOld;
    //多选 偏好
    static HWND labPreference;
    static HWND radioComedy;
    static HWND radioRomance;
    static HWND radioAction;
    static HWND radioCartoon;
    static HWND radioPlot;
    static HWND radioSuspense;
    static HWND radioSci_Fic;
    static HWND radioAdventure;
    static HWND radioCrime;
    //确认按钮
    static HWND btnSubmit;

    switch (message){
        case  WM_CREATE:
            hFont=CreateFont(
                -14,-7,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("微软雅黑")
            );

            //选择性别
            labSex=CreateWindow(
                TEXT("static"),TEXT("性别："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,30,80,26,
                hWnd,(HMENU)1,hInst,NULL
            );

            radioMale=CreateWindow(
                TEXT("button"), TEXT("男"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON  | WS_GROUP,
                95,30,50,26,
                hWnd,(HMENU)2,hInst,NULL
            );

            radioFemale=CreateWindow(
                TEXT("button"),TEXT("女"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                150,30,50,26,
                hWnd,(HMENU)3,hInst,NULL
            );

            //年龄
            labAge=CreateWindow(
                TEXT("static"),TEXT("年龄："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,70,80,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            radioChild=CreateWindow(
                TEXT("button"),TEXT("儿童"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,70,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            radioTeen=CreateWindow(
                TEXT("button"),TEXT("青少年"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,70,80,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            radioMiddleAge=CreateWindow(
                TEXT("button"), TEXT("中年人"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                250,70,80,26,
                hWnd,(HMENU)7,hInst,NULL
            );

            radioOld=CreateWindow(
                TEXT("button"), TEXT("老人"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                335,70,60,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            //偏好
            labPreference=CreateWindow(
                TEXT("static"),TEXT("偏好(选填)："),
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                10,110,80,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            radioComedy=CreateWindow(
                TEXT("button"),TEXT("喜剧"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,110,65,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            radioRomance=CreateWindow(
                TEXT("button"),TEXT("爱情"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,110,65,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            radioAction=CreateWindow(
                TEXT("button"),TEXT("动作"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                235,110,65,26,
                hWnd,(HMENU)12,hInst,NULL
            );

            radioCartoon=CreateWindow(
                TEXT("button"),TEXT("动画"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                305,110,65,26,
                hWnd,(HMENU)13,hInst,NULL
            );

            radioPlot=CreateWindow(
                TEXT("button"),TEXT("剧情"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                375,110,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            radioSuspense=CreateWindow(
                TEXT("button"),TEXT("悬疑"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                95,140,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            radioSci_Fic=CreateWindow(
                TEXT("button"),TEXT("科幻"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,140,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );

            radioAdventure=CreateWindow(
                TEXT("button"),TEXT("冒险"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                235,140,65,26,
                hWnd,(HMENU)17,hInst,NULL
            );

            radioCrime=CreateWindow(
                TEXT("button"),TEXT("犯罪/战争"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                305,140,100,26,
                hWnd,(HMENU)18,hInst,NULL
            );
            //确认按钮
            btnSubmit=CreateWindow(
                TEXT("button"),TEXT("确认"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT | SS_CENTER,
                210,200,80,30,
                hWnd,(HMENU)19,hInst,NULL
            );

            //性别
            SendMessage(labSex,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioMale,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioFemale,WM_SETFONT,(WPARAM)hFont,NULL);
            //年龄
            SendMessage(labAge,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioChild,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioTeen,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioMiddleAge,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioOld,WM_SETFONT,(WPARAM)hFont,NULL);
            //偏好
            SendMessage(labPreference,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioComedy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioRomance,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioAction,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioCartoon,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioPlot,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioSuspense,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioSci_Fic,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioAdventure,WM_SETFONT,(WPARAM)hFont, NULL);
            SendMessage(radioCrime,WM_SETFONT,(WPARAM)hFont,NULL);
            //确认按钮
            SendMessage(btnSubmit,WM_SETFONT,(WPARAM)hFont,NULL);
            //初始化
            if (uSex!=0) CheckRadioButton(hWnd,2,3,uSex+1);
            if (uAge!=0) CheckRadioButton(hWnd,5,8,uAge+4);
            if (uPreference!=0) CheckRadioButton(hWnd,10,18,uPreference+9);
            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
//如果有被选中的话
            if (wmEvent==BN_CLICKED)
            {
                switch(wmId)
                {
                    case 2:
                    case 3:
                        uSex=wParam-1;
                        break;
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        uAge=wParam-4;
                        break;
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                        uPreference=wParam-9;
                        break;
                    case 19:
                        wsprintf(szTextBuf,TEXT("用户信息提交成功"));
                        MessageBox(hWnd,szTextBuf,TEXT("信息提醒"),MB_OK);
                        SendMessage(hWnd,WM_DESTROY,NULL,NULL);
                        break;
                    default:return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            // TODO:  在此添加任意绘图代码...
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            fileclose_user_information();
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
