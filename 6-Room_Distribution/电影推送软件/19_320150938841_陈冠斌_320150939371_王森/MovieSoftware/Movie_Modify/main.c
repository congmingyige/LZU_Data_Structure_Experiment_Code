#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

HDC hdc,mdc;
HBITMAP bg;

struct movie movie[1000];
struct user user[1000];
long total_movie,pos_movie;
long total_user,pos_user,CurrentUser;
char filename[100];

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    //�����Ӱ��Ϣ
    fileopen_movie();
    //ģʽ �޸ĵ�Ӱ/�鿴��Ӱ
    fileopen_movie_introduce();

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
        TEXT("��Ӱ��̨����"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        300,  //��ʼ��ʱx���λ��
        5,  //��ʼ��ʱy���λ��
        825,  //���ڿ��
        825,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow(hwnd,iCmdShow);
    //���£����ƣ�����
    UpdateWindow(hwnd);

//��ʼ��
    //����ļ�·��
    GetModuleFileName(NULL,filename,100);
    *(strstr(filename,"MovieSoftware")+14)='\0';
    //��Ӱ��Ŵ�0��ʼ �����½�״̬,���½��ĵ�Ӱ��ŵ�ͬ�ڵ�Ӱ����
    pos_movie=total_movie;
    if (ModeInterface==0)
        //�޸ĵ�Ӱ �½� ���
        SendMessage(hwnd,WM_COMMAND,(WPARAM)48,NULL);
    else
        //�鿴��Ӱ ��תҳ��
        SendMessage(hwnd,WM_COMMAND,(WPARAM)1000,NULL);

    /**********�ڢ۲�����Ϣѭ��**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage(&msg);  //������Ϣ
        switch(msg.message)
        {
            case WM_KEYDOWN:
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('1')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)48,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('2')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)50,NULL);
                break;
        }
    }

    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    RECT rect;

    static bool vis_edit=true,vis_page=true,vis_check=true,vis_create=true;
    long i,page;
    //0:�½� 1:�޸�
    static int EditMode=0;
    static int DrawPrevious,DrawCurrent=1;
    char s[100],s1[100];

    static HPEN hPenRed;
    static HPEN hPenWhite;

    static HFONT hFont;
    static HFONT hFontTitle;
    static HFONT hFontNumber;
//��Ӱ��
    static HWND hLabMovieName;
    static HWND hEditMovieName;
//��Ӱ���
    static HWND hLabMovieMode;
    static HWND checkboxComedy;
    static HWND checkboxRomance;
    static HWND checkboxAction;
    static HWND checkboxCartoon;
    static HWND checkboxTeen;
    static HWND checkboxFeature;
    static HWND checkboxSci_Fic;
    static HWND checkboxThriller;
    static HWND checkboxOther;
//�ʺ���Ⱥ
    static HWND hLabMoviePeople;
    //����
    static HWND radioSad;
    static HWND radioDisappointed;
    static HWND radioRegret;
    static HWND radioNervious;
    //״̬
    static HWND radio1;
    static HWND radio2;
    static HWND radio3;
    static HWND radio4;
    //�Ա�
    static HWND radioBoy;
    static HWND radioGirl;
    //����
    static HWND radioChild;
    static HWND radioTeen;
    static HWND radioMiddleAge;
    static HWND radioOld;
//����
    static HWND hLabOverallMark;
    static HWND hEditOverallMark;
    static HWND hLabProfessorMark;
    static HWND hEditProfessorMark;
    static HWND hLabUserMark;
    static HWND hEditUserMark;
    static HWND hLabMarkStandard;
    static HWND hBtnMarkStandard;
    //��ӳʱ��͵ص�
    static HWND hLabTime;
    static HWND hEditTime;
    static HWND hLabPlace;
    static HWND hEditPlace;
    //��Ӱ���
    static HWND hEditIntroduce;
    //����ͼƬ�����ӡ���Ӱ ���Ե�ַ
    static HWND hLabPhotoAddress;
    static HWND hEditPhotoAddress;
    static HWND hLabTorrentAddress;
    static HWND hEditTorrentAddress;
    static HWND hLabFileAddress;
    static HWND hEditFileAddress;
    //ȷ�ϰ�ť
    static HWND hBtnModifySubmit;
    //�½���Ӱ���鿴��Ӱ��ť
    static HWND hBtnNewMovie;
    static HWND hBtnCheckMovie;
    static HWND hEditCheckMovie;
    //��Ӱ��Ϣ
    static HWND hBtnMovieInformation;
    //���沢�˳���ť
    static HWND hBtnSaveAndExit;

    //�ַ���,��������
    TCHAR szTextBuf[100],szNumBuf[100],szPassage[1000];

    switch(message)
    {
        case WM_CREATE:
            //��������
            hPenRed=CreatePen(PS_SOLID,2,RGB(255,0,0));
            hPenWhite=CreatePen(PS_SOLID,2,RGB(255,255,255));
            //��������
            hFont=CreateFont(
                -18,-9,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hFontTitle=CreateFont(
                -22,-11,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hFontNumber=CreateFont(
                -28,-14,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            //��Ӱ��
            hLabMovieName=CreateWindow(
                TEXT("static"),TEXT("��Ӱ��:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,40,120,40,
                hWnd,(HMENU)1,hInst,NULL
            );

            hEditMovieName=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                240,40,345,40,
                hWnd,(HMENU)2,hInst,NULL
            );
            //��Ӱ���
            hLabMovieMode=CreateWindow(
                TEXT("static"),TEXT("��Ӱ���:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,100,120,40,
                hWnd,(HMENU)3,hInst,NULL
            );

            checkboxComedy=CreateWindow(
                TEXT("button"),TEXT("ϲ��"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                215,92,65,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            checkboxRomance=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                285,92,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            checkboxAction=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                355,92,65,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            checkboxCartoon=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                425,92,65,26,
                hWnd,(HMENU)7,hInst,NULL
            );

            checkboxTeen=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                495,92,65,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            checkboxFeature=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                215,122,65,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            checkboxSci_Fic=CreateWindow(
                TEXT("button"),TEXT("�ƻ�"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                285,122,65,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            checkboxThriller=CreateWindow(
                TEXT("button"),TEXT("ð��"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                355,122,65,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            checkboxOther=CreateWindow(
                TEXT("button"),TEXT("����/ս��"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                425,122,110,26,
                hWnd,(HMENU)12,hInst,NULL
            );
            //�ʺ���Ⱥ
            hLabMoviePeople=CreateWindow(
                TEXT("static"),TEXT("�ʺ���Ⱥ:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,166,120,40,
                hWnd,(HMENU)13,hInst,NULL
            );
            //����
            radioSad=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                215,158,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            radioDisappointed=CreateWindow(
                TEXT("button"),TEXT("ʧ��"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                285,158,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            radioRegret=CreateWindow(
                TEXT("button"),TEXT("���"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                355,158,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );

            radioNervious=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                425,158,65,26,
                hWnd,(HMENU)17,hInst,NULL
            );
            //״̬
            radio1=CreateWindow(
                TEXT("button"),TEXT("�ٽ�����"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                215,188,95,26,
                hWnd,(HMENU)18,hInst,NULL
            );

            radio2=CreateWindow(
                TEXT("button"),TEXT("����ָ�"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                315,188,95,26,
                hWnd,(HMENU)19,hInst,NULL
            );

            radio3=CreateWindow(
                TEXT("button"),TEXT("ȱ������"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                415,188,95,26,
                hWnd,(HMENU)20,hInst,NULL
            );

            radio4=CreateWindow(
                TEXT("button"),TEXT("��������"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                515,188,95,26,
                hWnd,(HMENU)21,hInst,NULL
            );
            //�Ա�
            radioBoy=CreateWindow(
                TEXT("button"),TEXT("��"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                215,218,45,26,
                hWnd,(HMENU)22,hInst,NULL
            );

            radioGirl=CreateWindow(
                TEXT("button"),TEXT("Ů"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                265,218,45,26,
                hWnd,(HMENU)23,hInst,NULL
            );
            //����
            radioChild=CreateWindow(
                TEXT("button"),TEXT("��ͯ"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                315,218,60,26,
                hWnd,(HMENU)24,hInst,NULL
            );

            radioTeen=CreateWindow(
                TEXT("button"),TEXT("������"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                380,218,80,26,
                hWnd,(HMENU)25,hInst,NULL
            );

            radioMiddleAge=CreateWindow(
                TEXT("button"),TEXT("������"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                465,218,80,26,
                hWnd,(HMENU)26,hInst,NULL
            );

            radioOld=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                550,218,60,26,
                hWnd,(HMENU)27,hInst,NULL
            );

            //����
            //����
            hLabOverallMark=CreateWindow(
                TEXT("static"),TEXT("��������:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,255,120,40,
                hWnd,(HMENU)28,hInst,NULL
            );
            //����һ������
            hEditOverallMark=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                215,255,55,40,
                hWnd,(HMENU)29,hInst,NULL
            );

            //ר������
            hLabProfessorMark=CreateWindow(
                TEXT("static"),TEXT("ר������:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                280,255,120,40,
                hWnd,(HMENU)30,hInst,NULL
            );
            //ר��һ��Ҫ����
            hEditProfessorMark=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                405,255,55,40,
                hWnd,(HMENU)31,hInst,NULL
            );

            //�û�����
            hLabUserMark=CreateWindow(
                TEXT("static"),TEXT("�û�����:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                470,255,120,40,
                hWnd,(HMENU)32,hInst,NULL
            );

            hEditUserMark=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY,
                595,255,155,40,
                hWnd,(HMENU)33,hInst,NULL
            );

            sprintf(szTextBuf,TEXT("����:0.1~9.9,ר������%d%%,�û�����%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
            hLabMarkStandard=CreateWindow(
                TEXT("static"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                140,305,450,40,
                hWnd,(HMENU)34,hInst,NULL
            );

            hBtnMarkStandard=CreateWindow(
                TEXT("button"),TEXT("���ֹ���"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                620,305,80,40,
                hWnd,(HMENU)35,hInst,NULL
            );

            hLabTime=CreateWindow(
                TEXT("static"),TEXT("�й���ӳʱ��:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,355,150,40,
                hWnd,(HMENU)36,hInst,NULL
            );

            hEditTime=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                245,355,150,40,
                hWnd,(HMENU)37,hInst,NULL
            );

            hLabPlace=CreateWindow(
                TEXT("static"),TEXT("��Ƭ����/��ַ:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                405,355,170,40,
                hWnd,(HMENU)38,hInst,NULL
            );

            hEditPlace=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                580,355,170,40,
                hWnd,(HMENU)39,hInst,NULL
            );
            //��Ӱ���
            hEditIntroduce=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                90,405,660,170,
                hWnd,(HMENU)40,hInst,NULL
            );

            //����ͼƬ ���Ե�ַ
            hLabPhotoAddress=CreateWindow(
                TEXT("static"),TEXT("ͼƬ��ַ:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,585,120,40,
                hWnd,(HMENU)41,hInst,NULL
            );

            hEditPhotoAddress=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,585,510,40,
                hWnd,(HMENU)42,hInst,NULL
            );
            //�������� ���Ե�ַ
            hLabTorrentAddress=CreateWindow(
                TEXT("static"),TEXT("���ӵ�ַ:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,635,120,40,
                hWnd,(HMENU)43,hInst,NULL
            );

            hEditTorrentAddress=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,635,510,40,
                hWnd,(HMENU)44,hInst,NULL
            );
            //������Ƶ ���Ե�ַ
            hLabFileAddress=CreateWindow(
                TEXT("static"),TEXT("��Ƶ��ַ:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,685,120,40,
                hWnd,(HMENU)45,hInst,NULL
            );

            hEditFileAddress=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,685,510,40,
                hWnd,(HMENU)46,hInst,NULL
            );

            hBtnModifySubmit=CreateWindow(
                TEXT("button"),TEXT("ȷ��"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                300,735,80,40,
                hWnd,(HMENU)47,hInst,NULL
            );

            hBtnNewMovie=CreateWindow(
                TEXT("button"),TEXT("�½���Ӱ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                280,5,100,30,
                hWnd,(HMENU)48,hInst,NULL
            );

            hBtnCheckMovie=CreateWindow(
                TEXT("button"),TEXT("�޸ĵ�Ӱ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                390,5,100,30,
                hWnd,(HMENU)49,hInst,NULL
            );

            hEditCheckMovie=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                500,5,50,30,
                hWnd,(HMENU)50,hInst,NULL
            );

            hBtnMovieInformation=CreateWindow(
                TEXT("button"),TEXT("��Ӱ��Ϣ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                100,5,100,30,
                hWnd,(HMENU)51,hInst,NULL
            );

            hBtnSaveAndExit=CreateWindow(
                TEXT("button"),TEXT("���沢�˳�"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                390,735,100,40,
                hWnd,(HMENU)52,hInst,NULL
            );

            //��Ӱ��
            SendMessage(hLabMovieName,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditMovieName,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            //��Ӱ���
            SendMessage(hLabMovieMode,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(checkboxComedy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxRomance,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAction,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxCartoon,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxTeen,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxFeature,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxSci_Fic,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxThriller,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxOther,WM_SETFONT,(WPARAM)hFont,NULL);
            //�ʺ���Ⱥ
            SendMessage(hLabMoviePeople,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            //����
            SendMessage(radioSad,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioDisappointed,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioRegret,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioNervious,WM_SETFONT,(WPARAM)hFont,NULL);
            //״̬
            SendMessage(radio1,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radio2,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radio3,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radio4,WM_SETFONT,(WPARAM)hFont,NULL);
            //�Ա�
            SendMessage(radioBoy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioGirl,WM_SETFONT,(WPARAM)hFont,NULL);
            //����
            SendMessage(radioChild,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioTeen,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioMiddleAge,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioOld,WM_SETFONT,(WPARAM)hFont,NULL);
            //����
            SendMessage(hLabOverallMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditOverallMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabProfessorMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditProfessorMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabUserMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditUserMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabMarkStandard,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMarkStandard,WM_SETFONT,(WPARAM)hFont,NULL);
            //��ӳʱ��͵ص�
            SendMessage(hLabTime,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditTime,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabPlace,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditPlace,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            //��Ӱ���
            SendMessage(hEditIntroduce,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            //����ͼƬ�����ӡ���Ӱ ���Ե�ַ
            SendMessage(hLabPhotoAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditPhotoAddress,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabTorrentAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditTorrentAddress,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabFileAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditFileAddress,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            //ȷ�ϰ�ť
            SendMessage(hBtnModifySubmit,WM_SETFONT,(WPARAM)hFont,NULL);
            //�½���Ӱ���鿴��Ӱ��ť
            SendMessage(hBtnNewMovie,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnCheckMovie,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditCheckMovie,WM_SETFONT,(WPARAM)hFont,NULL);
            //��Ӱ��Ϣ
            SendMessage(hBtnMovieInformation,WM_SETFONT,(WPARAM)hFont,NULL);
            //���沢�˳���ť
            SendMessage(hBtnSaveAndExit,WM_SETFONT,(WPARAM)hFont,NULL);

            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch (wmId)
            {
                case 1000:
                    sprintf(szTextBuf,TEXT("%d"),ModeNumber+1);
                    SetWindowText(hEditCheckMovie,szTextBuf);
                    ShowWindow(hBtnNewMovie,SW_HIDE);
                    ShowWindow(hBtnCheckMovie,SW_HIDE);
                    ShowWindow(hEditCheckMovie,SW_HIDE);
                    ShowWindow(hBtnModifySubmit,SW_HIDE);
                    ShowWindow(hBtnSaveAndExit,SW_HIDE);
                    ShowWindow(hBtnMovieInformation,SW_HIDE);
                    break;
                //��Ӱ�� ��Ϊ����״̬ ����д�����������еĵ�Ӱ����ͬ��������Ϣ
                case 2:
                    GetWindowText(hEditCheckMovie,szTextBuf,100);
                    if (strlen(szTextBuf)==0 && EditMode==1)
                    {
                        vis_check=false;
                        vis_edit=false;
                        GetWindowText(hEditMovieName,szTextBuf,100);
                        for (i=0;i<total_movie;i++)
                            if (strcmp(movie[i].Name,szTextBuf)==0)
                            {
                                vis_edit=true;
                                break;
                            }
                        //����Ҳ�����ͬ���ֵĵ�Ӱ�������Ļ
                        if (!vis_edit)
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                        //����ҵ�����������
                        else
                        {
                            vis_create=true;
                            pos_movie=i;
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)102,NULL);
                        }
                    }
                    //�жϵ�Ӱ���Ƿ��Ѿ���ʹ��
                    vis_edit=false;
                    GetWindowText(hEditMovieName,szTextBuf,100);
                    for (i=0;i<total_movie;i++)
                        if (i!=pos_movie && strcmp(movie[i].Name,szTextBuf)==0)
                        {
                            vis_edit=true;
                            break;
                        }
                    if (vis_edit)
                    {
                        rect.left=510;
                        rect.right=800;
                        rect.top=730;
                        rect.bottom=780;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        DrawText(
                            hdc,
                            TEXT("��Ӱ�����ѱ�ʹ��"),
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    else
                    {
                        rect.left=510;
                        rect.right=800;
                        rect.top=730;
                        rect.bottom=780;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        for (i=0;i<strlen("��Ӱ�����ѱ�ʹ��");i++) szTextBuf[i]=' ';
                        szTextBuf[i]='\0';
                        DrawText(
                            hdc,
                            szTextBuf,
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    break;

                //�ı�ר������
                case 31:
                    GetWindowText(hEditProfessorMark,szTextBuf,100);
                    if (strlen(szTextBuf)==3 && szTextBuf[1]=='.' && szTextBuf[0]>='0' && szTextBuf[0]<='9' && szTextBuf[2]>='0' && szTextBuf[2]<='9')
                    {
                        movie[pos_movie].ProfessorMark=(szTextBuf[0]-48.0)+(szTextBuf[2]-48.0)/10.0;
                        //���ר�����֡��û�����ռ�����ı���
                        if (movie[pos_movie].UserNumber<5) movie[pos_movie].RatioMark=1.0;
                            else if (movie[pos_movie].UserNumber<=100) movie[pos_movie].RatioMark=0.7;
                                else if (movie[pos_movie].UserNumber<=1000) movie[pos_movie].RatioMark=0.5;
                                    else movie[pos_movie].RatioMark=0.3;
                        //������������
                        if (movie[pos_movie].UserNumber==0)
                            movie[pos_movie].OverallMark=movie[pos_movie].ProfessorMark;
                        else
                            movie[pos_movie].OverallMark=movie[pos_movie].ProfessorMark*movie[pos_movie].RatioMark+movie[pos_movie].UserMark/movie[pos_movie].UserNumber*(1-movie[pos_movie].RatioMark);
                        //�����������
                        sprintf(szNumBuf,TEXT("%.1f"),movie[pos_movie].OverallMark);
                        SetWindowText(hEditOverallMark,szNumBuf);
                        //���ר�����֡��û�����ռ�����ı���
                        sprintf(szTextBuf,TEXT("����:0.1~9.9,ר������%d%%,�û�����%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                        SetWindowText(hLabMarkStandard,szTextBuf);
                    }
                    break;

                //���ֹ���
                case 35:
                    wsprintf(szTextBuf,TEXT("�û�����������\r\n <5\t\t\tר��100%% �û�0%% \r\n 5~100\t\t\tר��70%% �û�30%% \r\n 101~1000\t\tר��50%% �û�50%% \r\n >1001\t\t\tר��30%% �û�70%%"));
                    MessageBox(hWnd,szTextBuf,TEXT("���ֹ���"),MB_ICONINFORMATION);
                    break;

                //��Ӱ���
                case 40:
                    GetWindowText(hEditIntroduce,szPassage,1000);
                    if (strlen(szPassage)==0)
                    {
                        rect.left=0;
                        rect.right=290;
                        rect.top=730;
                        rect.bottom=780;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        DrawText(
                            hdc,
                            TEXT("���޸ĵ�Ӱ���"),
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    else
                    {
                        rect.left=0;
                        rect.right=290;
                        rect.top=730;
                        rect.bottom=780;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        for (i=0;i<strlen("���޸ĵ�Ӱ���");i++)
                            szPassage[i]=' ';
                        szPassage[i]='\0';
                        DrawText(
                            hdc,
                            szPassage,
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    break;

                //ͼƬ��ַ
                case 42:
                    SendMessage(hWnd,WM_PAINT,(WPARAM)42,NULL);
                    break;
                //ȷ�ϰ�ť
                case 47:
                    //�ж��Ƿ����½�״̬
                    if (!vis_create)
                    {
                        MessageBox(hWnd,TEXT("��Ӱ�����޸�״̬�����½���̨"),TEXT("����"),MB_OK);
                        break;
                    }
                    GetWindowText(hEditMovieName,szTextBuf,100);
                    //��Ӱ
                    if (strlen(szTextBuf)==0)
                    {
                        MessageBox(hWnd,TEXT("��Ӱ���Ʋ���Ϊ��"),TEXT("����"),MB_OK);
                        break;
                    }
                    vis_edit=true;
                    for (i=0;i<total_movie;i++)
                        if (i!=pos_movie && strcmp(szTextBuf,movie[i].Name)==0)
                        {
                            vis_edit=false;
                            break;
                        }
                    if (!vis_edit)
                    {
                        MessageBox(hWnd,TEXT("��Ӱ�����ѱ�ʹ��"),TEXT("����"),MB_OK);
                        break;
                    }
                    //ר������
                    GetWindowText(hEditProfessorMark,szTextBuf,100);
                    if (strlen(szTextBuf)==0)
                    {
                        MessageBox(hWnd,TEXT("ר������δ��д"),TEXT("����"),MB_OK);
                        break;
                    }
                    if (!(strlen(szTextBuf)==3 && szTextBuf[1]=='.' && szTextBuf[0]>='0' && szTextBuf[0]<='9' && szTextBuf[2]>='0' && szTextBuf[2]<='9'))
                    {
                        MessageBox(hWnd,TEXT("ר��������д����"),TEXT("����"),MB_OK);
                        break;
                    }
                    //��ӳʱ��
                    GetWindowText(hEditTime,szTextBuf,100);
                    if (strlen(szTextBuf)==0)
                    {
                        MessageBox(hWnd,TEXT("��ӳʱ�䲻��Ϊ��"),TEXT("����"),MB_OK);
                        break;
                    }
                    vis_edit=true;
                    for (i=0;i<10;i++)
                        if (i!=4 && i!=7 && (szTextBuf[i]<'0' || szTextBuf[i]>'9'))
                        {
                            vis_edit=false;
                            break;
                        }
                    if (vis_edit==false || strlen(szTextBuf)!=10 || szTextBuf[4]!='-' || szTextBuf[7]!='-')
                    {
                        MessageBox(hWnd,TEXT("��ӳʱ����д����"),TEXT("����"),MB_OK);
                        break;
                    }
                    //����Ӱȷ�ϴ���ʱҪ total_movie++;
                    if (pos_movie==total_movie) total_movie++;
                    //ʱ��example 2008-01-01
                    GetWindowText(hEditTime,szTextBuf,100);
                    strcpy(s1,szTextBuf);
                    strncpy(s,s1,4);
                    s[4]='\0';
                    movie[pos_movie].year=atoi(s);
                    strncpy(s,s1+5,2);
                    s[2]='\0';
                    movie[pos_movie].month=atoi(s);
                    strncpy(s,s1+8,2);
                    s[2]='\0';
                    movie[pos_movie].day=atoi(s);
                    //����
                    GetWindowText(hEditMovieName,movie[pos_movie].Name,100);
                    GetWindowText(hEditPlace,movie[pos_movie].Place,100);
                    GetWindowText(hEditIntroduce,movie[pos_movie].Passage,1000);
                    GetWindowText(hEditPhotoAddress,movie[pos_movie].Photo,100);
                    GetWindowText(hEditTorrentAddress,movie[pos_movie].Torrent,100);
                    GetWindowText(hEditFileAddress,movie[pos_movie].File,100);
                    //��Ӱ���
                    for (i=1;i<10;i++)
                        if (IsDlgButtonChecked(hWnd,3+i)==BST_CHECKED) movie[pos_movie].Category[i]=1;
                            else movie[pos_movie].Category[i]=0;
                    //���顢״̬���Ա�����
                    for (i=14;i<=17;i++)
                        if (IsDlgButtonChecked(hWnd,i)==BST_CHECKED)
                        {
                            movie[pos_movie].Mood=i-13;
                            break;
                        }
                    for (i=18;i<=21;i++)
                        if (IsDlgButtonChecked(hWnd,i)==BST_CHECKED)
                        {
                            movie[pos_movie].Condition=i-17;
                            break;
                        }
                    for (i=22;i<=23;i++)
                        if (IsDlgButtonChecked(hWnd,i)==BST_CHECKED)
                        {
                            movie[pos_movie].Sex=i-21;
                            break;
                        }
                    for (i=24;i<=27;i++)
                        if (IsDlgButtonChecked(hWnd,i)==BST_CHECKED)
                        {
                            movie[pos_movie].Age=i-23;
                            break;
                        }
                    //�������֡�ר�����������޸Ķ����ģ�
                    //���û������ֺ��û�������������䣬�������ﲻ�ò���
                    MessageBox(hWnd,TEXT("�޸ĳɹ�"),TEXT("����"),NULL);
                    break;
                //�½� ���
                case 48:
                    vis_create=true;
                    //���¾���
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=0;
                    if (DrawPrevious!=DrawCurrent)
                        SendMessage(hWnd,WM_PAINT,(WPARAM)DrawCurrent,NULL);
                    EditMode=0;
                    //���ҳ��
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                    //��Ӱ��Ŵ�0��ʼ�������½��ĵ�Ӱ���Ϊtotal_movie
                    pos_movie=total_movie;
                    movie[pos_movie].Number=pos_movie;
                    movie[pos_movie].RatioMark=1.0;
                    movie[pos_movie].UserNumber=0;
                    movie[pos_movie].OverallMark=0;
                    movie[pos_movie].ProfessorMark=0;
                    movie[pos_movie].UserMark=0;
                    movie[pos_movie].Mood=0;
                    movie[pos_movie].Sex=0;
                    movie[pos_movie].Age=0;
                    movie[pos_movie].Condition=0;
                    for (i=1;i<=9;i++) movie[pos_movie].Category[i]=0;
                    SetWindowText(hEditMovieName,"");
                    break;
                //�޸ĵ�Ӱ��ť
                case 49:
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=1;
                    if (DrawPrevious!=DrawCurrent)
                        SendMessage(hWnd,WM_PAINT,(WPARAM)DrawCurrent,NULL);
                    EditMode=1;
                    SetWindowText(hEditCheckMovie,"");
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                    break;

                //��ת �޸ĵ�Ӱ
                case 50:
                    vis_create=true;
                    //���¾���
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=1;
                    if (DrawPrevious!=DrawCurrent)
                        SendMessage(hWnd,WM_PAINT,(WPARAM)DrawCurrent,NULL);
                    EditMode=1;
                    GetWindowText(hEditCheckMovie,szTextBuf,100);
                    if (strlen(szTextBuf)==0)
                    {
                        SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                        vis_create=false;
                        break;
                    }
                    vis_page=true;
                    if (szTextBuf[0]=='0') vis_page=false;
                    for (i=0;i<strlen(szTextBuf);i++)
                        if (szTextBuf[i]<48 || szTextBuf[i]>57)
                        {
                            vis_page=false;
                            break;
                        }
                    if (vis_page)
                    {
                        page=atoi(szTextBuf);
                        if (page<=total_movie)
                        {
                            vis_create=true;
                            pos_movie=page-1;
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)102,NULL);
                        }
                        else
                        {
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)101,NULL);
                            vis_create=false;
                        }
                    }
                    break;
                //��Ӱ��Ϣ
                case 51:
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,"movie.txt");
                    system(szTextBuf);
                    break;
                //���沢�˳���ť
                case 52:
                    fileclose_movie();
                    SendMessage(hWnd,WM_DESTROY,NULL,NULL);
                    break;
                //��մ���
                case 101:
                        //���Ϊ�½���Ӱ״̬
                    if (vis_check) SetWindowText(hEditMovieName,"");
                        //���Ϊ�޸ĵ�Ӱ��ҳ���༭��Ϊ��ʱ �Ͳ�Ҫ�޸ĵ�Ӱ������
                    else vis_edit=true;
                    //��Ӱ��� ��ʾ��
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)40,NULL);
                    SetWindowText(hEditTime,"");
                    SetWindowText(hEditPlace,"");
                    SetWindowText(hEditIntroduce,"");
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,"Photo\\");
                    SetWindowText(hEditPhotoAddress,szTextBuf);
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,"Torrent\\");
                    SetWindowText(hEditTorrentAddress,szTextBuf);
                    SetWindowText(hEditFileAddress,"");
                    //����
                    SetWindowText(hEditOverallMark,"");
                    SetWindowText(hEditProfessorMark,"");
                    SetWindowText(hEditUserMark,"0/0��");
                    SetWindowText(hLabMarkStandard,"����:0.1~9.9,ר������100%,�û�����0%");
                    //��յ�Ӱ���
                    for (i=1;i<10;i++)
                        CheckDlgButton(hWnd,3+i,BST_UNCHECKED);
                    //������顢״̬���Ա�����
                    CheckRadioButton(hWnd,14,17,NULL);
                    CheckRadioButton(hWnd,18,21,NULL);
                    CheckRadioButton(hWnd,22,23,NULL);
                    CheckRadioButton(hWnd,24,27,NULL);
                    //�������Σ�����ͼƬ
                    hdc=GetDC(hWnd);
                    if (ModeInterface==0)
                        Rectangle(hdc,610,40,740,210);
                    break;

                //��д����
                case 102:
                        //�������ͨ��ҳ����ת��Ӱ״̬
                    if (vis_check) SetWindowText(hEditMovieName,movie[pos_movie].Name);
                        //���Ϊ�޸ĵ�Ӱ��ҳ���༭��Ϊ��ʱ �Ͳ�Ҫ�޸ĵ�Ӱ������
                    else vis_check=true;
                    //��Ӱ��� ��ʾ��
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)40,NULL);
                    if (movie[pos_movie].month<10 && movie[pos_movie].day<10)
                        sprintf(szTextBuf,TEXT("%d-0%d-0%d"),movie[pos_movie].year,movie[pos_movie].month,movie[pos_movie].day);
                    else if (movie[pos_movie].month<10 && movie[pos_movie].day>=10)
                        sprintf(szTextBuf,TEXT("%d-0%d-%d"),movie[pos_movie].year,movie[pos_movie].month,movie[pos_movie].day);
                    else if (movie[pos_movie].month>=10 && movie[pos_movie].day<10)
                        sprintf(szTextBuf,TEXT("%d-%d-0%d"),movie[pos_movie].year,movie[pos_movie].month,movie[pos_movie].day);
                    else if (movie[pos_movie].month>=10 && movie[pos_movie].day>=10)
                        sprintf(szTextBuf,TEXT("%d-%d-%d"),movie[pos_movie].year,movie[pos_movie].month,movie[pos_movie].day);
                    SetWindowText(hEditTime,szTextBuf);
                    SetWindowText(hEditPlace,movie[pos_movie].Place);
                    SetWindowText(hEditIntroduce,movie[pos_movie].Passage);
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,movie[pos_movie].Photo);
                    SetWindowText(hEditPhotoAddress,szTextBuf);
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,movie[pos_movie].Torrent);
                    SetWindowText(hEditTorrentAddress,szTextBuf);
                    strcpy(szTextBuf,filename);
                    strcat(szTextBuf,movie[pos_movie].File);
                    SetWindowText(hEditFileAddress,szTextBuf);
                    //����
                    sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].OverallMark);
                    SetWindowText(hEditOverallMark,szTextBuf);
                    sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].ProfessorMark);
                    SetWindowText(hEditProfessorMark,szTextBuf);
                    if (movie[pos_movie].UserNumber==0)
                        sprintf(szTextBuf,"0/0��");
                    else
                        sprintf(szTextBuf,TEXT("%.1f/%d��"),movie[pos_movie].UserMark/movie[pos_movie].UserNumber,movie[pos_movie].UserNumber);
                    SetWindowText(hEditUserMark,szTextBuf);
                    sprintf(szTextBuf,TEXT("����:0.1~9.9,ר������%d%%,�û�����%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                    SetWindowText(hLabMarkStandard,szTextBuf);
                    //��ʾ��Ӱ���
                    for (i=1;i<10;i++)
                        if (movie[pos_movie].Category[i]==1)
                            CheckDlgButton(hWnd,3+i,BST_CHECKED);
                        else CheckDlgButton(hWnd,3+i,BST_UNCHECKED);
                    //��ʾ���顢״̬���Ա�����
                    if (movie[pos_movie].Mood!=-1)
                        CheckRadioButton(hWnd,14,17,13+movie[pos_movie].Mood);
                    if (movie[pos_movie].Condition!=-1)
                        CheckRadioButton(hWnd,18,21,17+movie[pos_movie].Condition);
                    if (movie[pos_movie].Sex!=-1)
                        CheckRadioButton(hWnd,22,23,21+movie[pos_movie].Sex);
                    if (movie[pos_movie].Age!=-1)
                        CheckRadioButton(hWnd,24,27,23+movie[pos_movie].Age);
                    //��ʾ ͼƬ
                    SendMessage(hWnd,WM_PAINT,(WPARAM)42,NULL);
                    break;

                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }
            break;


        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            switch (wParam)
            {
                case 0:
                    if (ModeInterface==1) break;
                    hdc=GetDC(hWnd);
                    //ѡ��ױ�����
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,390,5,NULL);
                    LineTo(hdc,390,35);
                    LineTo(hdc,490,35);
                    LineTo(hdc,490,5);
                    LineTo(hdc,390,5);
                    //ѡ����
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,280,5,NULL);
                    LineTo(hdc,280,35);
                    LineTo(hdc,380,35);
                    LineTo(hdc,380,5);
                    LineTo(hdc,280,5);
                    break;

                case 1:
                    if (ModeInterface==1) break;
                    hdc=GetDC(hWnd);
                    //ѡ��ױ�����
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,280,5,NULL);
                    LineTo(hdc,280,35);
                    LineTo(hdc,380,35);
                    LineTo(hdc,380,5);
                    LineTo(hdc,280,5);
                    //ѡ����
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,390,5,NULL);
                    LineTo(hdc,390,35);
                    LineTo(hdc,490,35);
                    LineTo(hdc,490,5);
                    LineTo(hdc,390,5);
                    break;

                case 42:
                    //����ͼƬ
                    hdc=GetDC(hWnd);
                    //�������θ���ԭ��ͼƬ
                    Rectangle(hdc,610,40,740,210);
                    GetWindowText(hEditPhotoAddress,szTextBuf,100);
                    hdc=GetDC(hWnd);
                    mdc=CreateCompatibleDC(hdc);
                    bg=(HBITMAP)LoadImage(
                        NULL,
                        szTextBuf,
                        IMAGE_BITMAP,120,160,LR_LOADFROMFILE
                    );
                    SelectObject(mdc,bg);
                    BitBlt(hdc,615,45,120,160,mdc,0,0,SRCAND);
                    break;
            }
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            //����޸Ļ���
            fileclose_movie_introduce();
            DeleteObject(hFont);
            DeleteObject(hFontTitle);
            DeleteObject(hFontNumber);
            DeleteObject(hPenRed);
            DeleteObject(hPenWhite);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
