#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    static TCHAR szClassName[] = TEXT("Win32Demo");  //窗口类名
    HWND     hwnd;  //窗口句柄
    MSG      msg;  //消息
    WNDCLASS wndclass;  //窗口类

    hInst = hInstance;

    /**********第①步：注册窗口类**********/
    //为窗口类的各个字段赋值
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //窗口风格
    wndclass.lpfnWndProc  = WndProc;  //窗口过程
    wndclass.cbClsExtra   = 0;  //暂时不需要理解
    wndclass.cbWndExtra   = 0;  //暂时不需要理解
    wndclass.hInstance    = hInstance;  //当前窗口句柄
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //窗口图标
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW);  //鼠标样式
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);;  //窗口背景画刷（白色）
    wndclass.lpszMenuName = NULL ;  //窗口菜单
    wndclass.lpszClassName= szClassName;  //窗口类名
    //注册窗口
    RegisterClass(&wndclass);

    /*****第②步：创建窗口(并让窗口显示出来)*****/
    hwnd = CreateWindow(
        szClassName,  //窗口名字
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

//窗口过程
LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
){
    PAINTSTRUCT ps;
    HDC hdc;
    HWND hStatic;

    switch (message){
        case  WM_CREATE:
            hStatic = CreateWindow(
                L"static", //静态文本框的类名
                L"C语言中文网",  //控件的文本
                WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | WS_BORDER /*带边框*/| SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/,
                20 /*X坐标*/, 20 /*Y坐标*/, 200 /*宽度*/, 100 /*高度*/,
                hWnd,  //父窗口句柄
                (HMENU)1,  //为控件指定一个唯一标识符
                hInst,  //当前程序实例句柄
                NULL
            );
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            // TODO:  在此添加任意绘图代码...
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam) ;
}
