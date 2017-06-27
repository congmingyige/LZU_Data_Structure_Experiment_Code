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

        DispatchMessage (&msg);  //分派消息
        TranslateMessage(&msg);  //翻译消息
    }

    return msg.wParam;

}

/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    RECT rect;

    static INT x,y;
    static BOOL vis=FALSE;

    static HFONT hFont;  //逻辑字体
    static HWND hLabUsername;  //静态文本框--用户名
    static HWND hLabPassword;  //静态文本框--密码
    static HWND hEditUsername;  //单行文本输入框
    static HWND hEditPassword;  //密码输入框
    static HWND hBtnLogin;  //登录按钮

    //定义缓冲区
    TCHAR szUsername[100];
    TCHAR szPassword[100];
    TCHAR szUserInfo[200];

    RegisterHotKey(hWnd,0x0001,MOD_CONTROL,'W');

    switch (message){
        case  WM_CREATE:
            //创建逻辑字体
            hFont = CreateFont(-14/*高*/, -7/*宽*/, 0, 0, 400 /*一般这个值设为400*/,
                FALSE/*斜体?*/, FALSE/*下划线?*/, FALSE/*删除线?*/,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                FF_DONTCARE, TEXT("微软雅黑")
            );
            //创建静态文本框控件--用户名
            hLabUsername = CreateWindow(TEXT("static"), TEXT("用户名："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*垂直居中*/ | SS_RIGHT /*水平居右*/,
                0 /*x坐标*/, 20 /*y坐标*/, 70 /*宽度*/, 26 /*高度*/,
                hWnd /*父窗口句柄*/, (HMENU)1 /*控件ID*/, hInst /*当前程序实例句柄*/, NULL
            );
            //创建静态文本框控件--密码
            hLabPassword = CreateWindow(TEXT("static"), TEXT("密码："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*垂直居中*/ | SS_RIGHT /*水平居右*/,
                0, 56, 70, 26,
                hWnd, (HMENU)2, hInst, NULL
            );
            //创建单行文本框控件
            hEditUsername = CreateWindow(TEXT("edit"), TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER /*边框*/ | ES_AUTOHSCROLL /*水平滚动*/,
                80, 20, 200, 26,
                hWnd, (HMENU)3, hInst, NULL
            );
            //创建密码输入框
            hEditPassword = CreateWindow(TEXT("edit"), TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD /*密码*/ | ES_AUTOHSCROLL /*水平滚动*/,
                80, 56, 200, 26,
                hWnd, (HMENU)4, hInst, NULL
            );

            //创建按钮控件
            hBtnLogin = CreateWindow(TEXT("button"), TEXT("登录"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,
                80, 92, 200, 30,
                hWnd, (HMENU)5, hInst, NULL
            );

            //依次设置控件的字体
            SendMessage(hLabUsername, WM_SETFONT, (WPARAM)hFont, NULL);
            SendMessage(hLabPassword, WM_SETFONT, (WPARAM)hFont, NULL);
            SendMessage(hEditUsername, WM_SETFONT, (WPARAM)hFont, NULL);
            SendMessage(hEditPassword, WM_SETFONT, (WPARAM)hFont, NULL);
            SendMessage(hBtnLogin, WM_SETFONT, (WPARAM)hFont, NULL);
            break;

         case WM_COMMAND:
            wmId    = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
            switch (wmId){
                case 5:  //按钮的HMENU参数
                    //获取输入框的数据
                    GetWindowText(hEditUsername, szUsername, 100);
                    GetWindowText(hEditPassword, szPassword, 100);
                    wsprintf(szUserInfo, TEXT("C语言中文网提示：\r\n您的用户账号：%s\r\n您的用户密码：%s"), szUsername, szPassword);
                    MessageBox(hWnd, szUserInfo, TEXT("信息提示"), MB_ICONINFORMATION);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;

        case WM_KEYDOWN:
            if ((GetKeyState('A')<0) && (GetKeyState(VK_CONTROL)<0)) DestroyWindow(hWnd);
            break;

        case WM_HOTKEY:
            if (wParam==0x0001)
            {
                    UnregisterHotKey(NULL,0x0001);
                    DestroyWindow(hWnd);			//释放热键
            }
            break;

        case WM_CHAR:
            if (wParam=='a') x-=10;
                else if (wParam=='d') x+=10;
                    else if (wParam=='w') y-=10;
                        else if (wParam=='s') y+=10;
            GetClientRect(hWnd,&rect);
            InvalidateRect(hWnd,&rect,TRUE);
            break;

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            // TODO:  在此添加任意绘图代码...
            Rectangle(hdc,x,y,x+30,y+30);
            EndPaint(hWnd,&ps);
            break;


        case WM_DESTROY:
            DeleteObject(hFont);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
