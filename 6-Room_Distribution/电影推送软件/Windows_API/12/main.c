#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
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

/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    int wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    static HFONT hFont;
    static HWND hLabUsername;
    static HWND hLabPassword;
    static HWND hEditUsername;
    static HWND hEditPassword;
    static HWND hBtnLogin;

    TCHAR szUsername[100];
    TCHAR szPassword[100];
    TCHAR szUserInfo[200];

    switch(message)
    {
        case WM_CREATE:
            hFont=CreateFont(
                -14,-7,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("微软雅黑")
            );
            hLabUsername=CreateWindow(
                TEXT("static"),TEXT("用户名："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                0,20,70,26,
                hWnd,(HMENU)1,hInst,NULL
            );
            hLabUsername=CreateWindow(
                TEXT("static"),TEXT("密码："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                0,56,70,26,
                hWnd,(HMENU)1,hInst,NULL
            );
            hEditUsername=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                80,20,200,26,
                hWnd,(HMENU)3,hInst,NULL
            );
            hEditPassword=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                80,56,200,26,
                hWnd,(HMENU)3,hInst,NULL
            );
            hBtnLogin=CreateWindow(
                TEXT("button"),TEXT("登录"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
                80,92,200,30,
                hWnd,(HMENU)5,hInst,NULL
            );

            SendMessage(hLabUsername,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hLabPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditUsername,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnLogin,WM_SETFONT,(WPARAM)hFont,NULL);
            break;
        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch(wmId)
            {
                case 5:
                    GetWindowText(hEditUsername,szUsername,100);
                    GetWindowText(hEditPassword,szPassword,100);

                    wsprintf(szUserInfo,TEXT("c语言中文网提示：\r\n您的用户账号：%s\r\n您的用户密码：%s"),szUsername,szPassword);
                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_ICONINFORMATION);

                    hBtnLogin=CreateWindow(
                        TEXT("button"),TEXT("登录成功"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
                        80,92,200,30,
                        hWnd,(HMENU)5,hInst,NULL
                    );

                    break;
                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }
        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            EndPaint(hWnd,&ps);
            break;
        case WM_DESTROY:
            DeleteObject(hFont);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}











