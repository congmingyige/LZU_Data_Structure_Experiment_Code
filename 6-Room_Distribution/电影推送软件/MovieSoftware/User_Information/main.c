#include <windows.h>
#include "define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

struct movie movie[1000];
struct user user[1000];
long pos_user=-1,total_user,total_movie;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    //����
    fileopen_user();
    fileopen_user_information();

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
        TEXT("��Ϣ����"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        500/*CW_USEDEFAULT*/,  //��ʼ��ʱx���λ��
        250/*CW_USEDEFAULT*/,  //��ʼ��ʱy���λ��
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

    /**********�ڢ۲�����Ϣѭ��**********/
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage (&msg);  //������Ϣ
    }

    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR szTextBuf[100];
    int wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    static HFONT hFont;  //�߼�����
    //��ѡ �Ա�
    static HWND labSex;
    static HWND radioMale;
    static HWND radioFemale;
    //��ѡ ����
    static HWND labDefine;
    static HWND radioStudent;
    static HWND radioWorker;
    static HWND radioOther;
    //��ѡ ����
    static HWND labAge;
    static HWND radioChild;
    static HWND radioTeen;
    static HWND radioMiddleAge;
    static HWND radioOld;
    //��ѡ ƫ��
    static HWND labPreference;
    static HWND radioComedy;
    static HWND radioRomance;
    static HWND radioAction;
    static HWND radioCartoon;
    static HWND radioPlot;
    static HWND radioSuspense;
    static HWND radioSci_Fic;
    static HWND radioAdventure;
    static HWND radioCrime;
    //ȷ�ϰ�ť
    static HWND btnSubmit;

    switch (message){
        case  WM_CREATE:
            hFont=CreateFont(
                -14,-7,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("΢���ź�")
            );

            //ѡ���Ա�
            labSex=CreateWindow(
                TEXT("static"),TEXT("�Ա�"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,30,80,26,
                hWnd,(HMENU)1,hInst,NULL
            );

            radioMale=CreateWindow(
                TEXT("button"), TEXT("��"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON  | WS_GROUP,
                95,30,50,26,
                hWnd,(HMENU)2,hInst,NULL
            );

            radioFemale=CreateWindow(
                TEXT("button"),TEXT("Ů"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                150,30,50,26,
                hWnd,(HMENU)3,hInst,NULL
            );

            //����
            labAge=CreateWindow(
                TEXT("static"),TEXT("���䣺"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,70,80,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            radioChild=CreateWindow(
                TEXT("button"),TEXT("��ͯ"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,70,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            radioTeen=CreateWindow(
                TEXT("button"),TEXT("������"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,70,80,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            radioMiddleAge=CreateWindow(
                TEXT("button"), TEXT("������"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                250,70,80,26,
                hWnd,(HMENU)7,hInst,NULL
            );

            radioOld=CreateWindow(
                TEXT("button"), TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                335,70,60,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            //ƫ��
            labPreference=CreateWindow(
                TEXT("static"),TEXT("ƫ��(ѡ��)��"),
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                10,110,80,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            radioComedy=CreateWindow(
                TEXT("button"),TEXT("ϲ��"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,110,65,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            radioRomance=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,110,65,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            radioAction=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                235,110,65,26,
                hWnd,(HMENU)12,hInst,NULL
            );

            radioCartoon=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                305,110,65,26,
                hWnd,(HMENU)13,hInst,NULL
            );

            radioPlot=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                375,110,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            radioSuspense=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                95,140,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            radioSci_Fic=CreateWindow(
                TEXT("button"),TEXT("�ƻ�"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,140,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );

            radioAdventure=CreateWindow(
                TEXT("button"),TEXT("ð��"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                235,140,65,26,
                hWnd,(HMENU)17,hInst,NULL
            );

            radioCrime=CreateWindow(
                TEXT("button"),TEXT("����/ս��"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                305,140,100,26,
                hWnd,(HMENU)18,hInst,NULL
            );
            //ȷ�ϰ�ť
            btnSubmit=CreateWindow(
                TEXT("button"),TEXT("ȷ��"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT | SS_CENTER,
                210,200,80,30,
                hWnd,(HMENU)19,hInst,NULL
            );

            //�Ա�
            SendMessage(labSex,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioMale,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioFemale,WM_SETFONT,(WPARAM)hFont,NULL);
            //����
            SendMessage(labAge,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioChild,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioTeen,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioMiddleAge,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioOld,WM_SETFONT,(WPARAM)hFont,NULL);
            //ƫ��
            SendMessage(labPreference,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioComedy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioRomance,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioAction,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioCartoon,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioPlot,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioSuspense,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioSci_Fic,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioAdventure,WM_SETFONT,(WPARAM)hFont, NULL);
            SendMessage(radioCrime,WM_SETFONT,(WPARAM)hFont,NULL);
            //ȷ�ϰ�ť
            SendMessage(btnSubmit,WM_SETFONT,(WPARAM)hFont,NULL);
            //��ʼ��
            if (uSex!=0) CheckRadioButton(hWnd,2,3,uSex+1);
            if (uAge!=0) CheckRadioButton(hWnd,5,8,uAge+4);
            if (uPreference!=0) CheckRadioButton(hWnd,10,18,uPreference+9);
            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
//����б�ѡ�еĻ�
            if (wmEvent==BN_CLICKED)
            {
                switch(wmId)
                {
                    case 2:
                    case 3:
                        uSex=wParam-1;
                        break;
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        uAge=wParam-4;
                        break;
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                        uPreference=wParam-9;
                        break;
                    case 19:
                        wsprintf(szTextBuf,TEXT("�û���Ϣ�ύ�ɹ�"));
                        MessageBox(hWnd,szTextBuf,TEXT("��Ϣ����"),MB_OK);
                        SendMessage(hWnd,WM_DESTROY,NULL,NULL);
                        break;
                    default:return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            // TODO:  �ڴ���������ͼ����...
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            fileclose_user_information();
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
