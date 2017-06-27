#include <windows.h>
#include <string.h>
#include "E:\\MovieSoftware\\define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

struct user user[1000];

long pos_user;

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
    hwnd=CreateWindow(
        szClassName,  //�����������
        TEXT("�û�"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        500,  //��ʼ��ʱx���λ��
        250,  //��ʼ��ʱy���λ��
        500,  //���ڿ��
        300,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow(hwnd,iCmdShow);
    //���£����ƣ�����
    UpdateWindow(hwnd);

    SendMessage(hwnd,WM_PAINT,(WPARAM)2,NULL);
//�޸�ֵ
    /**********�ڢ۲�����Ϣѭ��**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage(&msg);  //������Ϣ
        switch(msg.message)
        {
            case WM_KEYDOWN:
                //Enter
                if (GetKeyState(VK_RETURN)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)10,NULL);
                //Tab
                if (GetKeyState(VK_TAB)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)100,NULL);
                //Ctrl+W
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('W')<0)
                    SendMessage(hwnd,WM_DESTROY,NULL,NULL);
                //Ctrl+1 ��¼
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('1')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)7,NULL);
                //Ctrl+2 ע��
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('2')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)8,NULL);
                //Ctrl+3 ��������
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('3')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)9,NULL);
        }
    }
    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    extern struct user user[1000];

    //��ʱ�ӵ�
    static int pos=0;
    static int UserAns=2;
    static int UserPos=0;
    strcpy(user[1].Name,"test");
    strcpy(user[1].Password,"123456");
    strcpy(user[2].Name,"John");
    strcpy(user[2].Password,"12345678");

    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    MSG msg;
    HDC hdc;
    RECT rect,rect1,rect2,rect3;
    POINT p;

    //����
    static HFONT hFont;
    //DrawText������
    static HFONT hFonthWnd;
    //����
    static HPEN hPenRed;
    static HPEN hPenWhite;
    //��¼ ע�� ��������
    static HWND hLabUsername;
    static HWND hLabPassword;
    static HWND hEditUsername;
    static HWND hEditPassword;
    static HWND hLabNewPassword;
    static HWND hEditNewPassword;
    //��ť:��¼ ע�� �������� ѡ��
    static HWND hBtnLogin;
    static HWND hBtnRegister;
    static HWND hBtnReset;
    //ȷ�ϰ�ť
    static HWND hBtnLoginSubmit;

    INT i;
    //����״̬
    static int PreviousRect,CurrentRect=2;
    //1:��¼ 2:ע�� 3:�������� 0:�ѵ�¼ ����ģʽ
    static INT LoginMode=2;
    //��¼�û��ı��
    static INT CurrentUser=2;
    //���ζ���
    static INT DrawRectp1,DrawRectp2,DrawRectc1,DrawRectc2;

    TCHAR szUsername[50];
    TCHAR szPassword[50];
    TCHAR szNewPassword[50];
    TCHAR szUserInfo[200];
    TCHAR szTextBuf[100];

    switch(message)
    {
        case WM_CREATE:
            //��������
            hPenRed=CreatePen(PS_SOLID,2,RGB(255,0,0));
            hPenWhite=CreatePen(PS_SOLID,2,RGB(255,255,255));
            //��������
            hFont=CreateFont(
                -14,-7,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hFonthWnd=CreateFont(
                -30,-15,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hLabUsername=CreateWindow(
                TEXT("static"),TEXT("�û���"),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                70,50,70,26,
                hWnd,(HMENU)1,hInst,NULL
            );

            hLabPassword=CreateWindow(
                TEXT("static"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                70,90,70,26,
                hWnd,(HMENU)2,hInst,NULL
            );

            hEditUsername=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                150,50,200,26,
                hWnd,(HMENU)3,hInst,NULL
            );

            hEditPassword=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD,
                150,90,200,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            hLabNewPassword=CreateWindow(
                TEXT("static"),TEXT("������"),
                WS_CHILD | SS_CENTERIMAGE | SS_CENTER | SS_CENTERIMAGE,
                70,130,70,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            hEditNewPassword=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_BORDER | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD,
                150,130,200,26,
                hWnd,(HMENU)6,hInst,NULL
            );
            //ģʽ:��¼
            if (LoginMode==0) sprintf(szTextBuf,TEXT("�ǳ�"));
                else sprintf(szTextBuf,TEXT("��¼"));
            hBtnLogin=CreateWindow(
                TEXT("button"),szTextBuf,
                WS_CHILD | WS_VISIBLE,
                280,220,50,25,
                hWnd,(HMENU)7,hInst,NULL
            );
            //ģʽ:ע��
            hBtnRegister=CreateWindow(
                TEXT("button"),TEXT("ע��"),
                WS_CHILD | WS_VISIBLE,
                335,220,50,25,
                hWnd,(HMENU)8,hInst,NULL
            );
            //ģʽ:��������
            hBtnReset=CreateWindow(
                TEXT("button"),TEXT("��������"),
                WS_CHILD | WS_VISIBLE,
                390,220,80,25,
                hWnd,(HMENU)9,hInst,NULL
            );
            //ȷ�ϰ�ť
            hBtnLoginSubmit=CreateWindow(
                TEXT("button"),TEXT("ȷ��"),
                WS_CHILD | WS_VISIBLE,
                210,170,80,40,
                hWnd,(HMENU)10,hInst,NULL
            );

            SendMessage(hLabUsername,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hLabPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditUsername,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hLabNewPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditNewPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnLogin,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnRegister,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnReset,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnLoginSubmit,WM_SETFONT,(WPARAM)hFont,NULL);
            //ȷ�ϸ��ֿ������/��ʾ
            switch(LoginMode)
            {
                case 0:
                    ShowWindow(hLabUsername,SW_HIDE);
                    ShowWindow(hEditUsername,SW_HIDE);
                    ShowWindow(hLabPassword,SW_HIDE);
                    ShowWindow(hEditPassword,SW_HIDE);
                    ShowWindow(hBtnLoginSubmit,SW_HIDE);
                    break;
                case 2:
                case 3:
                    ShowWindow(hLabNewPassword,SW_SHOW);
                    ShowWindow(hEditNewPassword,SW_SHOW);
                    break;
            }
            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch(wmId)
            {
                //Tab
                case 100:
                    GetCursorPos(&p);
                    GetWindowRect(hEditUsername,&rect1);
                    GetWindowRect(hEditPassword,&rect2);
                    GetWindowRect(hEditNewPassword,&rect3);
                    switch(LoginMode)
                    {
                        case 1:
                            if (rect1.left<=p.x && rect1.right>=p.x && rect1.top<=p.y && rect1.bottom>=p.y)
                            {
                                SetCursorPos(rect2.left,rect2.top);
                                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                                mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            }
                            else
                            {
                                SetCursorPos(rect1.left,rect1.top);
                                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                                mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            }
                            break;
                        case 2:
                        case 3:
                            if (rect1.left<=p.x && rect1.right>=p.x && rect1.top<=p.y && rect1.bottom>=p.y)
                            {
                                SetCursorPos(rect2.left,rect2.top);
                                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                                mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            }
                            else if (rect2.left<=p.x && rect2.right>=p.x && rect2.top<=p.y && rect2.bottom>=p.y)
                            {
                                SetCursorPos(rect3.left,rect3.top);
                                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                                mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            }
                            else
                            {
                                SetCursorPos(rect1.left,rect1.top);
                                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                                mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            }
                            break;
                    }
                    break;
                //����¼��ť ��������λ��
                case 101:
                    GetWindowText(hEditUsername,szUsername,50);
                    if (strcmp(szUsername,"")==0)
                    {
                        GetWindowRect(hEditUsername,&rect);
                        SetCursorPos(rect.left,rect.top);
                        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                    }
                    else
                    {
                        GetWindowText(hEditPassword,szPassword,50);
                        if (strcmp(szPassword,"")==0)
                        {
                            GetWindowRect(hEditPassword,&rect);
                            SetCursorPos(rect.left,rect.top);
                            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        }
                        else
                        {
                            GetWindowRect(hBtnLoginSubmit,&rect);
                            SetCursorPos((rect.left+rect.right)/2,(rect.top+rect.bottom)/2);
                        }
                    }
                    break;
                //��ע��/�������밴ť ��������λ��
                case 102:
                    GetWindowText(hEditUsername,szUsername,50);
                    if (strcmp(szUsername,"")==0)
                    {
                        GetWindowRect(hEditUsername,&rect);
                        SetCursorPos(rect.left,rect.top);
                        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                    }
                    else
                    {
                        GetWindowText(hEditPassword,szPassword,50);
                        if (strcmp(szPassword,"")==0)
                        {
                            GetWindowRect(hEditPassword,&rect);
                            SetCursorPos(rect.left,rect.top);
                            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        }
                        else
                        {
                            GetWindowText(hEditNewPassword,szPassword,50);
                            if (strcmp(szPassword,"")==0)
                            {
                                GetWindowRect(hEditNewPassword,&rect);
                                SetCursorPos(rect.left,rect.top);
                                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                                mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            }
                            else
                            {
                                GetWindowRect(hBtnLoginSubmit,&rect);
                                SetCursorPos((rect.left+rect.right)/2,(rect.top+rect.bottom)/2);
                            }
                        }
                    }
                    break;

                //��¼
                case 7:
                    if (LoginMode==0)
                    {
                        SendMessage(hWnd,WM_PAINT,(WPARAM)4,NULL);
                        SetWindowText(hBtnLogin,"��¼");
                        ShowWindow(hLabUsername,SW_SHOW);
                        ShowWindow(hEditUsername,SW_SHOW);
                        ShowWindow(hLabPassword,SW_SHOW);
                        ShowWindow(hEditPassword,SW_SHOW);
                    }
                    SetWindowText(hLabPassword,"����");
                    ShowWindow(hLabNewPassword,SW_HIDE);
                    ShowWindow(hEditNewPassword,SW_HIDE);
                    //״̬ͳ��
                    LoginMode=1;
                    //����ͳ��
                    PreviousRect=CurrentRect;
                    CurrentRect=1;
                    //���¾���
                    SendMessage(hWnd,WM_PAINT,(WPARAM)7,NULL);
                    //�������λ��
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                    break;
                //ע��
                case 8:
                    if (LoginMode==0)
                    {
                        ShowWindow(hLabUsername,SW_SHOW);
                        ShowWindow(hEditUsername,SW_SHOW);
                        ShowWindow(hLabPassword,SW_SHOW);
                        ShowWindow(hEditPassword,SW_SHOW);
                    }
                    SetWindowText(hLabPassword,"������");
                    SetWindowText(hLabNewPassword,"����һ��");
                    ShowWindow(hLabNewPassword,SW_SHOW);
                    ShowWindow(hEditNewPassword,SW_SHOW);
                    //״̬ͳ��
                    LoginMode=2;
                    //����ͳ��
                    PreviousRect=CurrentRect;
                    CurrentRect=2;
                    //���¾���
                    SendMessage(hWnd,WM_PAINT,(WPARAM)8,NULL);
                    //�������λ��
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)102,NULL);
                    break;
                //��������
                case 9:
                    if (LoginMode==0)
                    {
                        ShowWindow(hLabUsername,SW_SHOW);
                        ShowWindow(hEditUsername,SW_SHOW);
                        ShowWindow(hLabPassword,SW_SHOW);
                        ShowWindow(hEditPassword,SW_SHOW);
                    }
                    SetWindowText(hLabPassword,"������");
                    SetWindowText(hLabNewPassword,"������");
                    ShowWindow(hLabNewPassword,SW_SHOW);
                    ShowWindow(hEditNewPassword,SW_SHOW);
                    //״̬ͳ��
                    LoginMode=3;
                    //����ͳ��
                    PreviousRect=CurrentRect;
                    CurrentRect=3;
                    //���¾���
                    SendMessage(hWnd,WM_PAINT,(WPARAM)9,NULL);
                    //�������λ��
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)102,NULL);
                    break;
                //�ύ
                case 10:
                    GetWindowText(hEditUsername,szUsername,100);
                    GetWindowText(hEditPassword,szPassword,100);
                    GetWindowText(hEditNewPassword,szNewPassword,100);
                    switch(LoginMode)
                    {
                            //��¼
                            case 1:
                                //����û�������
                                pos=find_name(UserAns,szUsername);
                                if (pos==0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���¼ʧ�ܣ�\r\n�û�������\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                }
                                //������벻��ȷ
                                else if (strcmp(szPassword,user[pos].Password)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���¼ʧ�ܣ�\r\n�������벻��ȷ\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                }
                                //����ɹ�
                                else
                                {
                                    wsprintf(szUserInfo,TEXT("%s\r\n��¼�ɹ�"),hEditUsername);
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_OK);
                                    ShowWindow(hWnd,SW_HIDE);
                                }
                                break;
                            //ע��
                            case 2:
                                //����û��Ѿ�����
                                if (find_name(UserAns,szUsername)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û�ע��ʧ�ܣ�\r\n�û��Ѿ�����\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //������������С��6λ
                                else if (strlen(szPassword)<6)
                                {
                                    wsprintf(szUserInfo,TEXT("�û�ע��ʧ�ܣ�\r\n���õ�����Ӧ��С��6λ\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //���������������벻һ��
                                else if (strcmp(szPassword,szNewPassword)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û�ע��ʧ�ܣ�\r\n������������벻һ��\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //����ɹ�
                                else
                                {
                                    wsprintf(szUserInfo,TEXT("�û�ע��ɹ���\r\n�û��˺ţ�%s\r\n�û����룺%s"),szUsername,szPassword);
                                    UserAns++;
                                    strcpy(user[UserAns].Name,szUsername);
                                    strcpy(user[UserAns].Password,szPassword);
                                    InitUser(UserAns);
                                    wsprintf(szUserInfo,TEXT("�������Ƹ�����Ϣ"));
                                    int nSelect=MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_YESNO);
                                    if (nSelect==IDYES)
                                    {
                                        //���Ƹ�����Ϣ
                                    }
                                    ShowWindow(hWnd,SW_HIDE);
                                }
                                break;
                            //��������
                            case 3:
                                //����û�������
                                pos=find_name(UserAns,szUsername);
                                if (pos==0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���������ʧ�ܣ�\r\n�û�������\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //�����������벻��ȷ
                                else if (strcmp(szPassword,user[pos].Password)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���������ʧ�ܣ�\r\n�������벻��ȷ\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //��������������С��6λ
                                else if (strlen(szNewPassword)<6)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���������ʧ�ܣ�\r\n���õ�����Ӧ��С��6λ\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //����ɹ�
                                else
                                {
                                    wsprintf(szUserInfo,TEXT("�û���������ɹ���\r\n�û��˺ţ�%s\r\n���û����룺%s"),szUsername,szNewPassword);
                                    strcpy(user[pos].Password,szPassword);
                                    wsprintf(szUserInfo,TEXT("�������Ƹ�����Ϣ"));
                                    int nSelect=MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_YESNO);
                                    if (nSelect==IDYES)
                                    {
                                        //���Ƹ�����Ϣ
                                    }
                                    ShowWindow(hWnd,SW_HIDE);
                                }
                                break;
                        ShowWindow(hLabUsername,SW_SHOW);
                        ShowWindow(hEditUsername,SW_SHOW);
                        ShowWindow(hLabPassword,SW_SHOW);
                        ShowWindow(hEditPassword,SW_SHOW);
                            default:
                                return DefWindowProc(hWnd,message,wParam,lParam);
                    }
                    break;
            }
            break;

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch(wmId)
            {
                //���¾���
                case 7:
                case 8:
                case 9:
                    hdc=GetDC(hWnd);
                    DrawRectp1=225+55*PreviousRect;
                    DrawRectp2=275+55*PreviousRect+30*(PreviousRect==3);
                    DrawRectc1=225+55*CurrentRect;
                    DrawRectc2=275+55*CurrentRect+30*(CurrentRect==3);
                    //ѡ��ױ�����
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,DrawRectp1,220,NULL);
                    LineTo(hdc,DrawRectp1,245);
                    LineTo(hdc,DrawRectp2,245);
                    LineTo(hdc,DrawRectp2,220);
                    LineTo(hdc,DrawRectp1,220);
                    //ѡ����
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,DrawRectc1,220,NULL);
                    LineTo(hdc,DrawRectc1,245);
                    LineTo(hdc,DrawRectc2,245);
                    LineTo(hdc,DrawRectc2,220);
                    LineTo(hdc,DrawRectc1,220);
                    break;
                //ѡ���� ��ʼ����¼״̬
                //�ѵ�¼״̬

                case 0:
                    if (LoginMode!=0) break;
                    hdc=GetDC(hWnd);
                    GetClientRect(hWnd,&rect);
                    rect.top-=100;
                    rect.bottom-=100;
                    sprintf(szTextBuf,TEXT("%s�ѵ�¼"),user[1].Name);
                    SelectObject(hdc,hFonthWnd);
                    DrawText(
                        hdc,
                        szTextBuf,
                        -1,
                        &rect,
                        DT_SINGLELINE | DT_CENTER | DT_VCENTER
                    );
                    break;

                //��ʼ��״̬
                case 1:
                case 2:
                case 3:
                    hdc=GetDC(hWnd);
                    DrawRectp1=225+55*LoginMode;
                    DrawRectp2=275+55*LoginMode+30*(LoginMode==3);
                    //ѡ����
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,DrawRectp1,220,NULL);
                    LineTo(hdc,DrawRectp1,245);
                    LineTo(hdc,DrawRectp2,245);
                    LineTo(hdc,DrawRectp2,220);
                    LineTo(hdc,DrawRectp1,220);
                    break;

                //�ӵ�¼״̬���˳�
                case 4:
                    hdc=GetDC(hWnd);
                    GetClientRect(hWnd,&rect);
                    rect.top-=100;
                    rect.bottom-=100;
                    for (i=0;i<strlen(user[CurrentUser].Name)+strlen("�ѵ�¼");i++)
                        szTextBuf[i]=' ';
                    szTextBuf[i]='\0';
                    SelectObject(hdc,hFonthWnd);
                    DrawText(
                        hdc,
                        szTextBuf,
                        -1,
                        &rect,
                        DT_SINGLELINE | DT_CENTER | DT_VCENTER
                    );
                    break;
            }
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            DeleteObject(hFont);
            DeleteObject(hFonthWnd);
            DeleteObject(hPenRed);
            DeleteObject(hPenWhite);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
