#include <windows.h>
//ǰ�涨��
LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    static TCHAR szClassName[] = TEXT("HelloWin");  //��������
    HWND     hwnd,hwnd1;  //���ھ��
    MSG      msg;  //��Ϣ
    WNDCLASS wndclass,wndclass1;  //������

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
    hwnd=CreateWindow(
        szClassName,  //�����������
        TEXT(""),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        300,  //��ʼ��ʱx���λ��
        20,  //��ʼ��ʱy���λ��
        800,  //���ڿ��
        800,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow(hwnd,iCmdShow);
    //���£����ƣ�����
    UpdateWindow(hwnd);

////////////////////////////////////////////////
//wndcloass�����޸�
    wndclass1.style = CS_HREDRAW | CS_VREDRAW;  //���ڷ��
    wndclass1.lpfnWndProc  = WndProc1;  //���ڹ���   !!!�޸�����
    wndclass1.cbClsExtra   = 0;  //��ʱ����Ҫ���
    wndclass1.cbWndExtra   = 0;  //��ʱ����Ҫ���
    wndclass1.hInstance    = hInstance;  //��ǰ���ھ��
    wndclass1.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //����ͼ��
    wndclass1.hCursor      = LoadCursor (NULL, IDC_ARROW);  //�����ʽ
    wndclass1.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);  //���ڱ�����ˢ
    wndclass1.lpszMenuName = NULL ;  //���ڲ˵�
    wndclass1.lpszClassName= szClassName;  //��������
//�޸�����
    RegisterClass(&wndclass1);
//�޸�����
    hwnd1=CreateWindow(
        szClassName,  //�����������
        TEXT(""),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        150,  //��ʼ��ʱx���λ��
        20,  //��ʼ��ʱy���λ��
        800,  //���ڿ��
        800,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );
//�޸�����
    ShowWindow(hwnd1,iCmdShow);
    UpdateWindow(hwnd1);

    /**********�ڢ۲�����Ϣѭ��**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage(&msg);  //������Ϣ
    }

    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
//���һ������
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
                TEXT("button"),  //��ť�ؼ�������
                TEXT("�����������"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*��ƽ��ʽ*/,
                30 /*X����*/, 110 /*Y����*/, 150 /*���*/, 50/*�߶�*/,
                hWnd, (HMENU)2 /*�ؼ�Ψһ��ʶ��*/, hInst, NULL
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
