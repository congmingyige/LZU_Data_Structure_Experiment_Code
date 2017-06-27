#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

HDC hdc,mdc;
HBITMAP bg;

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
    hwnd=CreateWindow(
        szClassName,  //窗口类的名字
        TEXT(""),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        0,  //初始化时x轴的位置
        0,  //初始化时y轴的位置
        1800,  //窗口宽度
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
////1
//            hdc=GetDC(hwnd);
//            mdc=CreateCompatibleDC(hdc);
//            bg=(HBITMAP)LoadImage(
//                NULL,
//                "E:\\test.bmp",
//                IMAGE_BITMAP,
//                100,100,
//                LR_LOADFROMFILE
//            );
//            SelectObject(mdc,bg);
//            BitBlt(hdc,100,100,100,100,mdc,0,0,SRCAND);
////2
//            hdc=GetDC(hwnd);
//            Rectangle(hdc,95,95,205,205);

//3
            hdc=GetDC(hwnd);
            mdc=CreateCompatibleDC(hdc);
            bg=(HBITMAP)LoadImage(
                NULL,
                "C:\\Users\\Lenovo\\Desktop\\Garden_Hotel.jpg",
                IMAGE_BITMAP,
                100,100,
                LR_LOADFROMFILE
            );
            SelectObject(mdc,bg);
            BitBlt(hdc,100,100,100,100,mdc,0,0,SRCAND);


/**********第③步：消息循环**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage(&msg);  //分派消息
    }

    return msg.wParam;
}

/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    INT wmId,wmEvent;
    PAINTSTRUCT ps;

    switch(message)
    {
        case WM_CREATE:
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

