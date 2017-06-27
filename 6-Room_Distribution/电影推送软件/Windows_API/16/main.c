#include <windows.h>
//前面定义
LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    static TCHAR szClassName[] = TEXT("HelloWin");  //窗口类名
    HWND     hwnd,hwnd1;  //窗口句柄
    MSG      msg;  //消息
    WNDCLASS wndclass,wndclass1;  //窗口类

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
        300,  //初始化时x轴的位置
        20,  //初始化时y轴的位置
        800,  //窗口宽度
        800,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );

    //显示窗口
    ShowWindow(hwnd,iCmdShow);
    //更新（绘制）窗口
    UpdateWindow(hwnd);

////////////////////////////////////////////////
//wndcloass名字修改
    wndclass1.style = CS_HREDRAW | CS_VREDRAW;  //窗口风格
    wndclass1.lpfnWndProc  = WndProc1;  //窗口过程   !!!修改这里
    wndclass1.cbClsExtra   = 0;  //暂时不需要理解
    wndclass1.cbWndExtra   = 0;  //暂时不需要理解
    wndclass1.hInstance    = hInstance;  //当前窗口句柄
    wndclass1.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //窗口图标
    wndclass1.hCursor      = LoadCursor (NULL, IDC_ARROW);  //鼠标样式
    wndclass1.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);  //窗口背景画刷
    wndclass1.lpszMenuName = NULL ;  //窗口菜单
    wndclass1.lpszClassName= szClassName;  //窗口类名
//修改名字
    RegisterClass(&wndclass1);
//修改名字
    hwnd1=CreateWindow(
        szClassName,  //窗口类的名字
        TEXT(""),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        150,  //初始化时x轴的位置
        20,  //初始化时y轴的位置
        800,  //窗口宽度
        800,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );
//修改名字
    ShowWindow(hwnd1,iCmdShow);
    UpdateWindow(hwnd1);

    /**********第③步：消息循环**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage(&msg);  //分派消息
    }

    return msg.wParam;
}

/**********第④步：窗口过程**********/
//添加一个窗口
LRESULT CALLBACK WndProc1(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    return DefWindowProc(hWnd,message,wParam,lParam);
}


LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;


    static HWND hBtn;

    switch(message)
    {
        case WM_CREATE:
            hBtn = CreateWindow(
                TEXT("button"),  //按钮控件的类名
                TEXT("点击这里试试"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,
                30 /*X坐标*/, 110 /*Y坐标*/, 150 /*宽度*/, 50/*高度*/,
                hWnd, (HMENU)2 /*控件唯一标识符*/, hInst, NULL
            );

            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch (wmId)
            {

                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }
            break;

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
