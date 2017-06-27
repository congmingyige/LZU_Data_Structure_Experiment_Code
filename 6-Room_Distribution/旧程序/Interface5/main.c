#include <windows.h>
#include <string.h>
long t=0;
    HWND hwnd1;  //窗口句柄
    HWND hwnd2;


/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC         hdc;  //设备环境句柄
    PAINTSTRUCT ps;
    RECT        rect;

    ///如把窗口进行，拉伸(移动不能)，窗口的值就会改变;窗口内按按钮也不能
    t=(t+1)%10000000;
//    if (t%100==0)
//        ShowWindow (hwnd1, SW_HIDE);
//    else if (t%100==50)
//        ShowWindow (hwnd1, SW_SHOW);

    INT wmId,wmEvent;
    char szTextBuf[100];
    switch (message){
        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch (wmId)
            {
                case 1:
                    MessageBox(hwnd,TEXT("haha"),TEXT("评分规则"),MB_ICONINFORMATION);
                    break;
            }
            break;
        //窗口绘制消息
        case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps) ;
            GetClientRect (hwnd, &rect) ;
            sprintf(szTextBuf,TEXT("%ld"),t);
            DrawText(
                hdc,
                szTextBuf,
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

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    static TCHAR szClassName[] = TEXT("HelloWin");  //窗口类名
    MSG      msg;  //消息
    WNDCLASS wndclass;  //窗口类

    /**********第①步：注册窗口类**********/
    //为窗口类的各个字段赋值
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //窗口风格
    wndclass.lpfnWndProc  = WndProc;  //窗口过程 !!!
    wndclass.cbClsExtra   = 0;  //暂时不需要理解
    wndclass.cbWndExtra   = 0;  //暂时不需要理解
    wndclass.hInstance    = hInstance;  //当前窗口句柄 !!!
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //窗口图标
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW);  //鼠标样式
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);  //窗口背景画刷
    wndclass.lpszMenuName = NULL ;  //窗口菜单
    wndclass.lpszClassName= szClassName;  //窗口类名

    //注册窗口
    RegisterClass(&wndclass);

    /*****第②步：创建窗口(并让窗口显示出来)*****/
    hwnd1 = CreateWindow(
        szClassName,  //窗口类的名字
        TEXT("1"),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        CW_USEDEFAULT,  //初始化时x轴的位置
        CW_USEDEFAULT,  //初始化时y轴的位置
        500,  //窗口宽度
        300,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄     ///窗口生成放在主函数里，没有窗口菜单句柄才能工作 (HMENU)1
        hInstance,  //当前窗口的句柄   ///正常：hInstance，可以改变，设为0吗？
        NULL  //不使用该值
    );

    //显示窗口
    ShowWindow (hwnd1, iCmdShow);
    //更新（绘制）窗口
    UpdateWindow (hwnd1);

    hwnd2 = CreateWindow(
        szClassName,  //窗口类的名字
        TEXT("2"),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        200,  //初始化时x轴的位置
        100,  //初始化时y轴的位置
        500,  //窗口宽度
        300,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );
    ShowWindow (hwnd2, SW_SHOW);
    UpdateWindow (hwnd2);

    HWND name;
    name=CreateWindow(
                TEXT("button"),TEXT("a"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,20,60,30,
                hwnd1,(HMENU)1,hInstance,NULL   //属于哪个窗口就写哪里，从此以后就在该父窗口内
            );
    HWND age;
    age=CreateWindow(
                TEXT("static"),TEXT("b"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,100,120,40,
                hwnd2,(HMENU)2,hInstance,NULL
            );

    /**********第③步：消息循环**********/
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage (&msg);  //分派消息
        switch(msg.message)
        {
            case WM_KEYDOWN:
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('1')<0)
                {
                    t++;
                }
                break;
        }
    }

    return msg.wParam;
}
