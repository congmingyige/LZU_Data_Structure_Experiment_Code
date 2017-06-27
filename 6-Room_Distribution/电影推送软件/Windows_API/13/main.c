#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

POINT p;
RECT rect1,rect2,rect3;
HFONT hFont;  //�߼�����
HWND hLabUsername;  //��̬�ı���--�û���
HWND hLabPassword;  //��̬�ı���--����
HWND hEditUsername;  //�����ı������
HWND hEditPassword;  //���������
HWND hBtnLogin;  //��¼��ť

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

        DispatchMessage (&msg);  //������Ϣ
        TranslateMessage(&msg);  //������Ϣ
        //�����˵���Ϣ,���ı����°�Enter
        //Enter
        if (msg.message==WM_KEYDOWN && msg.wParam==VK_RETURN)
            SendMessage(hwnd,WM_COMMAND,(WPARAM)5,NULL);
        //Tab
        if (msg.message==WM_KEYDOWN && msg.wParam==VK_TAB)
        {
            GetCursorPos(&p);
            GetWindowRect(hEditUsername,&rect1);
            GetWindowRect(hEditPassword,&rect2);
            GetWindowRect(hBtnLogin,&rect3);
            if (rect1.left<=p.x && rect1.right>=p.x && rect1.top<=p.y && rect1.bottom>=p.y)
                SetCursorPos(rect2.left,rect2.top);
            else if (rect2.left<=p.x && rect2.right>=p.x && rect2.top<=p.y && rect2.bottom>=p.y)
                SetCursorPos((rect3.left+rect3.right)/2,(rect3.top+rect3.bottom)/2);
            else
                SetCursorPos(rect1.left,rect1.top);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
            mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
        }
        //Ctrl+W ������case WM_KEYDOWN: ���ڷ��ı����ڰ�Ctrl+W
        if (GetKeyState(VK_CONTROL)<0)
        {
            DestroyWindow(hwnd);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
            mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
        }
    }

    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    //���建����
    TCHAR szUsername[100];
    TCHAR szPassword[100];
    TCHAR szUserInfo[200];

    switch (message){
        case  WM_CREATE:
            //�����߼�����
            hFont = CreateFont(-14/*��*/, -7/*��*/, 0, 0, 400 /*һ�����ֵ��Ϊ400*/,
                FALSE/*б��?*/, FALSE/*�»���?*/, FALSE/*ɾ����?*/,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                FF_DONTCARE, TEXT("΢���ź�")
            );
            //������̬�ı���ؼ�--�û���
            hLabUsername = CreateWindow(TEXT("static"), TEXT("�û�����"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*��ֱ����*/ | SS_RIGHT /*ˮƽ����*/,
                0 /*x����*/, 20 /*y����*/, 70 /*���*/, 26 /*�߶�*/,
                hWnd /*�����ھ��*/, (HMENU)1 /*�ؼ�ID*/, hInst /*��ǰ����ʵ�����*/, NULL
            );
            //������̬�ı���ؼ�--����
            hLabPassword = CreateWindow(TEXT("static"), TEXT("���룺"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*��ֱ����*/ | SS_RIGHT /*ˮƽ����*/,
                0, 56, 70, 26,
                hWnd, (HMENU)2, hInst, NULL
            );
            //���������ı���ؼ�
            hEditUsername = CreateWindow(TEXT("edit"), TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER /*�߿�*/ | ES_AUTOHSCROLL /*ˮƽ����*/,
                80, 20, 200, 26,
                hWnd, (HMENU)3, hInst, NULL
            );
            //�������������
            hEditPassword = CreateWindow(TEXT("edit"), TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD /*����*/ | ES_AUTOHSCROLL /*ˮƽ����*/,
                80, 56, 200, 26,
                hWnd, (HMENU)4, hInst, NULL
            );

            //������ť�ؼ�
            hBtnLogin = CreateWindow(TEXT("button"), TEXT("��¼"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*��ƽ��ʽ*/,
                80, 92, 200, 30,
                hWnd, (HMENU)5, hInst, NULL
            );

            //�������ÿؼ�������
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
                case 5:  //��ť��HMENU����
                    //��ȡ����������
                    GetWindowText(hEditUsername, szUsername, 100);
                    GetWindowText(hEditPassword, szPassword, 100);
                    wsprintf(szUserInfo, TEXT("C������������ʾ��\r\n�����û��˺ţ�%s\r\n�����û����룺%s"), szUsername, szPassword);
                    MessageBox(hWnd, szUserInfo, TEXT("��Ϣ��ʾ"), MB_ICONINFORMATION);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;

        case WM_KEYDOWN:
            if (GetKeyState(VK_CONTROL)<0 && GetKeyState('W')<0)
            {
                exit(0);
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            // TODO:  �ڴ���������ͼ����...
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
