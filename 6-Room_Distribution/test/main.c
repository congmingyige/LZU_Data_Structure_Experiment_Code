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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    PAINTSTRUCT ps;
    HDC hdcWnd;
    HDC hdcStatic;

    static HFONT hFont;  //逻辑字体
    static HWND hStatic;  //静态文本框控件
    static HBRUSH hBrush;  //画刷

    switch (message){
        case  WM_CREATE:
            //创建画刷
            hBrush = CreateSolidBrush( RGB(0x41, 0x96, 0x4F) );

            //创建逻辑字体
            hFont = CreateFont(-14/*高*/, -7/*宽*/, 0, 0, 700 /*700表示粗体*/,
                FALSE/*斜体?*/, FALSE/*下划线?*/, FALSE/*删除线?*/,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                FF_DONTCARE, TEXT("微软雅黑")
            );
            //创建静态文本框控件
            hStatic = CreateWindow(TEXT("static"), TEXT("欢迎来到C语言中文网！"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER,
                20 /*x坐标*/, 20 /*y坐标*/, 240 /*宽度*/, 60 /*高度*/,
                hWnd /*父窗口句柄*/, (HMENU)1 /*控件ID*/, hInst /*当前程序实例句柄*/, NULL
            );

            //设置控件的字体
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, NULL);
            break;

        case WM_CTLCOLORSTATIC:
            hdcStatic = (HDC)wParam;
            SetTextColor( hdcStatic, RGB(255, 255, 255) );  //白色
            SetBkColor( hdcStatic, RGB(0x41, 0x96, 0x4F) );  //翠绿色
            return (INT_PTR)hBrush;

        case WM_PAINT:
            hdcWnd = BeginPaint(hWnd, &ps);
            // TODO:  在此添加任意绘图代码...
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            DeleteObject(hBrush);
            DeleteObject(hFont);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
