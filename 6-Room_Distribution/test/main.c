#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    static TCHAR szClassName[] = TEXT("HelloWin");  //��������
    HWND     hwnd;  //���ھ��
    MSG      msg;  //��Ϣ
    WNDCLASS wndclass;  //������

    hInst=hInstance;

    /**********�ڢٲ���ע�ᴰ����**********/
    //Ϊ������ĸ����ֶθ�ֵ
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //���ڷ��
    wndclass.lpfnWndProc  = WndProc;  //���ڹ���
    wndclass.cbClsExtra   = 0;  //��ʱ����Ҫ���
    wndclass.cbWndExtra   = 0;  //��ʱ����Ҫ���
    wndclass.hInstance    = hInstance;  //��ǰ���ھ��
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //����ͼ��
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW);  //�����ʽ
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);  //���ڱ�����ˢ
    wndclass.lpszMenuName = NULL ;  //���ڲ˵�
    wndclass.lpszClassName= szClassName;  //��������

    //ע�ᴰ��
    RegisterClass(&wndclass);

    /*****�ڢڲ�����������(���ô�����ʾ����)*****/
    hwnd = CreateWindow(
        szClassName,  //�����������
        TEXT("Welcome"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        CW_USEDEFAULT,  //��ʼ��ʱx���λ��
        CW_USEDEFAULT,  //��ʼ��ʱy���λ��
        500,  //���ڿ��
        300,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow (hwnd, iCmdShow);
    //���£����ƣ�����
    UpdateWindow (hwnd);

    /**********�ڢ۲�����Ϣѭ��**********/
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage (&msg);  //������Ϣ
    }

    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    PAINTSTRUCT ps;
    HDC hdcWnd;
    HDC hdcStatic;

    static HFONT hFont;  //�߼�����
    static HWND hStatic;  //��̬�ı���ؼ�
    static HBRUSH hBrush;  //��ˢ

    switch (message){
        case  WM_CREATE:
            //������ˢ
            hBrush = CreateSolidBrush( RGB(0x41, 0x96, 0x4F) );

            //�����߼�����
            hFont = CreateFont(-14/*��*/, -7/*��*/, 0, 0, 700 /*700��ʾ����*/,
                FALSE/*б��?*/, FALSE/*�»���?*/, FALSE/*ɾ����?*/,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                FF_DONTCARE, TEXT("΢���ź�")
            );
            //������̬�ı���ؼ�
            hStatic = CreateWindow(TEXT("static"), TEXT("��ӭ����C������������"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER,
                20 /*x����*/, 20 /*y����*/, 240 /*���*/, 60 /*�߶�*/,
                hWnd /*�����ھ��*/, (HMENU)1 /*�ؼ�ID*/, hInst /*��ǰ����ʵ�����*/, NULL
            );

            //���ÿؼ�������
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, NULL);
            break;

        case WM_CTLCOLORSTATIC:
            hdcStatic = (HDC)wParam;
            SetTextColor( hdcStatic, RGB(255, 255, 255) );  //��ɫ
            SetBkColor( hdcStatic, RGB(0x41, 0x96, 0x4F) );  //����ɫ
            return (INT_PTR)hBrush;

        case WM_PAINT:
            hdcWnd = BeginPaint(hWnd, &ps);
            // TODO:  �ڴ���������ͼ����...
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
