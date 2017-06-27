#include <windows.h>
typedef HWND (WINAPI *PROCGETCONSOLEWINDOW)();
PROCGETCONSOLEWINDOW GetConsoleWindow;

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

BOOL RegisterWindow(LPCSTR lpcWndName,HINSTANCE hInstance)
{
    ATOM nAtom=0;

    WNDCLASS wndClass={0};

    wndClass.style=CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc=WindowProc;
    wndClass.cbClsExtra=0;
    wndClass.cbWndExtra=0;
    wndClass.hInstance=hInstance;
    wndClass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(100));
    wndClass.hCursor=NULL;
    wndClass.hbrBackground=(HBRUSH)COLOR_GRAYTEXT;
    wndClass.lpszMenuName=NULL;
    wndClass.lpszClassName=lpcWndName;

    nAtom=RegisterClass(&wndClass);
    return nAtom;
}

HWND CreWindow(LPCTSTR lpClassName,HINSTANCE hInstance)
{
    HWND hWnd=NULL;
    hWnd=CreateWindow(lpClassName,"Hello World",
                      WS_OVERLAPPEDWINDOW,
                      0,0,500,500,
                      NULL,NULL,hInstance,NULL);
    return hWnd;
}

void DisplayWindow(HWND hWnd)
{
    ShowWindow(hWnd,SW_SHOW);
//如果窗口更新的区域不为空，UpdateWindow函数就发送一个WM_PAINT消息来更新指定窗口的客户区。
    UpdateWindow(hWnd);
}

void ProcessMessage()
{
    MSG msg={0};
    while (GetMessage(&msg,NULL,0,0))
    {
        DispatchMessage(&msg);
    }
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
    HMODULE hKernel32 = GetModuleHandle("kernel32");
    GetConsoleWindow = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32,"GetConsoleWindow");
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    HWND hWnd=NULL;
    LPCSTR lpClassName="Menu";
    RegisterWindow(lpClassName,hInstance);
    hWnd=CreWindow(lpClassName,hInstance);
    DisplayWindow(hWnd);


    HINSTANCE z1_hInstance=hInstance;
    HWND z1_hwnd;
    z1_hwnd=CreateWindow(lpClassName,"SonChuangKo",
                 WS_OVERLAPPEDWINDOW,
                 CW_USEDEFAULT,CW_USEDEFAULT,250,250,
                 NULL,NULL,z1_hInstance,NULL);
    ShowWindow(z1_hwnd,SW_SHOW);
    UpdateWindow(z1_hwnd);


    ProcessMessage();
    return 0;
}
