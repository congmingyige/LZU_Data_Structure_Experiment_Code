#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define maxn 100000
#define maxx 100
#define maxy 1000
#define maxz 10
#define maxlen 100

struct node
{
    //vis=tree����÷�����Ա�ʹ��
    bool vis;
    //use=tree����÷������ڱ�ʹ��
    bool use;
    char name[maxlen+1];
    //0:�У�1:Ů��2:����
    long age;
    long sex;
    long YY,MM,DD,hh,mm,ss;
//    long room_grade;
//    long room_number;
//    long bed_number;
}info[maxx+1][maxy+1][maxz+1];
char notice[1000]="�𾴵ı���  Dear customers (patrons)\nΪ�����Ľ����Ͱ�ȫ���벻Ҫ�ڿͷ����лƶĶ���\nFor the sake of your health and safety, please do not gamble,take drugs, or take part in vice activities  (in prostitution)\nΪ�����ĲƲ���ȫ�����������Ʊ��ܺ�������Ĺ�����Ʒ��\nFor the sake of safe custody of your valuables or own belongings\n������ʧ�����Ƶ�Ų�����\nThis hotel bears no responsibility for any losses.\n������Ҫ�Ƶ����ʱ����ֱ�Ӳ����ܻ����롰0����������ʱΪ������\nPlease dial \"0\" when you require our services. We are always happy to serve you.\n\nԤף���ڹ��ݻ�԰�Ƶ�ס������\n";
char GetSex[3][6]={"��","Ů","δ��д"};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND,UINT,UINT_PTR,DWORD);
void CALLBACK TimerProc1(HWND,UINT,UINT_PTR,DWORD);
void init();
void print();

HINSTANCE hInst;
HWND hLabTime;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    init();

    hInst=hInstance;
    static TCHAR szClassName[] = TEXT("HelloWin");  //��������
    HWND hwnd;  //���ھ��
    HFONT hFontNumber;
    MSG msg;  //��Ϣ
    WNDCLASS wndclass;  //������

    /**********�ڢٲ���ע�ᴰ����**********/
    //Ϊ������ĸ����ֶθ�ֵ
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //���ڷ��
    wndclass.lpfnWndProc  = WndProc;  //���ڹ���
    wndclass.cbClsExtra   = 0;  //��ʱ����Ҫ���
    wndclass.cbWndExtra   = 0;  //��ʱ����Ҫ���
    wndclass.hInstance    = hInstance;  //��ǰ���ھ��    //Ӧ�����������ֲ�ͬ���ڣ��Ӷ�������ĳ������ڲ�ͬ����ִ�в�ͬ���  hwnd.hInstance???
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
        TEXT("��ӭ��ס���ݻ�԰�Ƶ� ���� ���綩��"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        400,  //��ʼ��ʱx���λ��
        15,  //��ʼ��ʱy���λ��
        800,  //���ڿ��
        800,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow(hwnd,SW_SHOW);
    //���£����ƣ�����
    UpdateWindow(hwnd);


    hFontNumber=CreateFont(
        -22,-11,0,0,400,
        FALSE,FALSE,FALSE,DEFAULT_CHARSET,
        OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
        FF_DONTCARE,TEXT("Arial")
    );

    SYSTEMTIME Time;
    TCHAR szTextBuf[100];

    GetLocalTime(&Time);
    sprintf(szTextBuf,"%04ld/%02ld/%02ld-%02ld:%02ld:%02ld\0",Time.wYear,Time.wMonth,Time.wDay,Time.wHour,Time.wMinute,Time.wSecond);

    hLabTime=CreateWindow(
        TEXT("static"),szTextBuf,
        WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
        300,700,450,40,
        hwnd,(HMENU)0,hInst,NULL
    );
    SendMessage(hLabTime,WM_SETFONT,(WPARAM)hFontNumber,NULL);

    SetTimer(hwnd,1,1000,TimerProc);                //ʱ����ʾ
    SendMessage(hwnd,WM_PAINT,(WPARAM)0,NULL);      //���ֺ�ͼƬ��ʾ

    /**********�ڢ۲�����Ϣѭ��**********/
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage (&msg);  //������Ϣ
    }

    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC         hdc;  //�豸�������
    PAINTSTRUCT ps;
    RECT        rect;
    HDC mdc;
    HBITMAP bg;
    LOGFONT logFont;
    static HBRUSH hBrush;
    INT wmId,wmEvent;   //��������������Խ����޸�edit����WM_COMMAND����Ϣ
    hBrush=CreateSolidBrush(RGB(255,255,255));

    TCHAR szTextBuf[100];
    char filename[300];
    char strx[5],stry[5],strz[5];
    int i;
    static int sx,sy,sz;
    static bool vis=false;

    static HFONT hFontTitle,hFontCh,hFontMode,hFontMainTitle;
    static HWND hLabTime;
    static HWND hLabName,hEditName;
    static HWND hLabAge,hEditAge;
    static HWND hLabSexMode,checkboxMale,checkboxFemale,checkboxNoneSex;
    static HWND hLabRoomLevel,hEditRoomLevel;
    static HWND hLabRoomNum,hEditRoomNum;
    static HWND hLabBedNum,hEditBedNum;
    static HWND hBtnSubmit;
    static HWND hLabTip;
    static HWND hLabAdd,hEditAddx,hEditAddy,hEditAddz,hBtnAdd;
    static HWND hLabDel,hEditDelx,hEditDely,hEditDelz,hBtnDel;

    switch (message){
        //�մ���ʱִ��WM_CREATE,�Ժ���ִ��
        case WM_CREATE:
            //��������
            hFontTitle=CreateFont(
                -22,-11,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hFontCh=CreateFont(
                -28,-14,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hFontMode=CreateFont(
                -18,-9,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hFontMainTitle=CreateFont(
                -30,-15,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("�����п�")
            );

            hLabName=CreateWindow(
                TEXT("static"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                100,100,90,40,
                hwnd,(HMENU)1,hInst,NULL
            );

            hEditName=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                210,100,390,40,
                hwnd,(HMENU)2,hInst,NULL
            );

            hLabAge=CreateWindow(
                TEXT("static"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                100,160,90,40,
                hwnd,(HMENU)1,hInst,NULL
            );

            hEditAge=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                210,160,50,40,
                hwnd,(HMENU)2,hInst,NULL
            );

            hLabSexMode=CreateWindow(
                TEXT("static"),TEXT("�Ա�"),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | SS_CENTERIMAGE,
                280,160,90,40,
                hwnd,(HMENU)3,hInst,NULL
            );

            checkboxMale=CreateWindow(
                TEXT("button"),TEXT("��"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                390,167,40,26,
                hwnd,(HMENU)4,hInst,NULL
            );

            checkboxFemale=CreateWindow(
                TEXT("button"),TEXT("Ů"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                440,167,40,26,
                hwnd,(HMENU)5,hInst,NULL
            );

            checkboxNoneSex=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                490,167,65,26,
                hwnd,(HMENU)6,hInst,NULL
            );

            //�ı�checkbox��checked״̬
            CheckDlgButton(hwnd,6,1);

            hLabRoomLevel=CreateWindow(
                TEXT("static"),TEXT("�ͷ��ȼ�"),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                100,220,120,40,
                hwnd,(HMENU)7,hInst,NULL
            );

            hEditRoomLevel=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                240,220,40,40,
                hwnd,(HMENU)8,hInst,NULL
            );

            hLabRoomNum=CreateWindow(
                TEXT("static"),TEXT("�����"),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                300,220,120,40,
                hwnd,(HMENU)9,hInst,NULL
            );

            hEditRoomNum=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                440,220,60,40,
                hwnd,(HMENU)10,hInst,NULL
            );

            hLabBedNum=CreateWindow(
                TEXT("static"),TEXT("��λ��"),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                520,220,120,40,
                hwnd,(HMENU)11,hInst,NULL
            );

            hEditBedNum=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                660,220,40,40,
                hwnd,(HMENU)12,hInst,NULL
            );

            hBtnSubmit=CreateWindow(
                TEXT("button"),TEXT("�ύ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                350,350,100,40,
                hwnd,(HMENU)13,hInst,NULL
            );

            hLabTip=CreateWindow(
                TEXT("static"),TEXT(""),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE/*| ES_CENTER | ES_READONLY*/,
                100,280,600,40,
                hwnd,(HMENU)14,hInst,NULL
            );
            SetWindowText(hLabTip,TEXT("�����������������"));

            //???
            hLabAdd=CreateWindow(
                TEXT("static"),TEXT("���"),
                WS_CHILD | SS_CENTER | SS_CENTERIMAGE,
                100,200,90,40,
                hwnd,(HMENU)15,hInst,NULL
            );

            hEditAddx=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                210,200,40,40,
                hwnd,(HMENU)16,hInst,NULL
            );

            hEditAddy=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                260,200,40,40,
                hwnd,(HMENU)17,hInst,NULL
            );

            hEditAddz=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                310,200,40,40,
                hwnd,(HMENU)18,hInst,NULL
            );

            hBtnAdd=CreateWindow(
                TEXT("button"),TEXT("ȷ��"),
                WS_CHILD | WS_BORDER | BS_CENTER | BS_VCENTER,
                380,200,80,40,
                hwnd,(HMENU)19,hInst,NULL
            );

            hLabDel=CreateWindow(
                TEXT("static"),TEXT("ɾ��"),
                WS_CHILD | SS_CENTER | SS_CENTERIMAGE,
                100,300,90,40,
                hwnd,(HMENU)20,hInst,NULL
            );

            hEditDelx=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                210,300,40,40,
                hwnd,(HMENU)21,hInst,NULL
            );

            hEditDely=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                260,300,40,40,
                hwnd,(HMENU)22,hInst,NULL
            );

            hEditDelz=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
                310,300,40,40,
                hwnd,(HMENU)23,hInst,NULL
            );

            hBtnDel=CreateWindow(
                TEXT("button"),TEXT("ȷ��"),
                WS_CHILD | WS_BORDER | BS_CENTER | BS_VCENTER,
                380,300,80,40,
                hwnd,(HMENU)24,hInst,NULL
            );


            SendMessage(hLabName,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditName,WM_SETFONT,(WPARAM)hFontCh,NULL);

            SendMessage(hLabAge,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditAge,WM_SETFONT,(WPARAM)hFontCh,NULL);

            SendMessage(hLabSexMode,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(checkboxMale,WM_SETFONT,(WPARAM)hFontMode,NULL);
            SendMessage(checkboxFemale,WM_SETFONT,(WPARAM)hFontMode,NULL);
            SendMessage(checkboxNoneSex,WM_SETFONT,(WPARAM)hFontMode,NULL);

            SendMessage(hLabRoomLevel,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditRoomLevel,WM_SETFONT,(WPARAM)hFontCh,NULL);

            SendMessage(hLabRoomNum,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditRoomNum,WM_SETFONT,(WPARAM)hFontCh,NULL);

            SendMessage(hLabBedNum,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditBedNum,WM_SETFONT,(WPARAM)hFontCh,NULL);

            SendMessage(hBtnSubmit,WM_SETFONT,(WPARAM)hFontTitle,NULL);

            SendMessage(hLabTip,WM_SETFONT,(WPARAM)hFontCh,NULL);

            SendMessage(hLabAdd,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditAddx,WM_SETFONT,(WPARAM)hFontCh,NULL);
            SendMessage(hEditAddy,WM_SETFONT,(WPARAM)hFontCh,NULL);
            SendMessage(hEditAddz,WM_SETFONT,(WPARAM)hFontCh,NULL);
            SendMessage(hBtnAdd,WM_SETFONT,(WPARAM)hFontTitle,NULL);

            SendMessage(hLabDel,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditDelx,WM_SETFONT,(WPARAM)hFontCh,NULL);
            SendMessage(hEditDely,WM_SETFONT,(WPARAM)hFontCh,NULL);
            SendMessage(hEditDelz,WM_SETFONT,(WPARAM)hFontCh,NULL);
            SendMessage(hBtnDel,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            break;

        case WM_CTLCOLORSTATIC:
            if ((HWND)lParam==hLabTip)
            {
                SetTextColor((HDC)wParam,0x8B1A1A);
                SetBkColor((HDC)wParam,0xFAFAD2);
                return (INT_PTR)hBrush;
            }
            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam); //��������������Խ����޸�edit����WM_COMMAND����Ϣ
            switch (wmId)
            {
//                case 2:
//                    GetWindowText(hEditName,szTextBuf,100);
//                    if (strcmp(szTextBuf,"AdminGardenHotel")==0)
//                    {
//                        //MessageBox.show("������{0}��ֵ", n);
//
//                        ShowWindow(hLabName,SW_HIDE);
////                        ShowWindow(hEditName,SW_HIDE);
//
//                        ShowWindow(hLabAge,SW_HIDE);
//                        ShowWindow(hEditAge,SW_HIDE);
//
//                        ShowWindow(hLabSexMode,SW_HIDE);
//                        ShowWindow(checkboxMale,SW_HIDE);
//                        ShowWindow(checkboxFemale,SW_HIDE);
//                        ShowWindow(checkboxNoneSex,SW_HIDE);
//
//                        ShowWindow(hLabRoomLevel,SW_HIDE);
//                        ShowWindow(hEditRoomLevel,SW_HIDE);
//
//                        ShowWindow(hLabRoomNum,SW_HIDE);
//                        ShowWindow(hEditRoomNum,SW_HIDE);
//
//                        ShowWindow(hLabBedNum,SW_HIDE);
//                        ShowWindow(hEditBedNum,SW_HIDE);
//
//                        ShowWindow(hBtnSubmit,SW_HIDE);
//
//                        ShowWindow(hLabTip,SW_HIDE);
//
//                        ShowWindow(hLabAdd,SW_SHOW);
//                        ShowWindow(hEditAddx,SW_SHOW);
//                        ShowWindow(hEditAddy,SW_SHOW);
//                        ShowWindow(hEditAddz,SW_SHOW);
//                        ShowWindow(hBtnAdd,SW_SHOW);
//
//                        ShowWindow(hLabDel,SW_SHOW);
//                        ShowWindow(hEditDelx,SW_SHOW);
//                        ShowWindow(hEditDely,SW_SHOW);
//                        ShowWindow(hEditDelz,SW_SHOW);
//                        ShowWindow(hBtnDel,SW_SHOW);
//
//                    }
//                    break;
                case 8:
                case 10:
                case 12:
                    GetWindowText(hEditRoomLevel,strx,5);
                    GetWindowText(hEditRoomNum,stry,5);
                    GetWindowText(hEditBedNum,strz,5);

                    vis=true;
                    if (vis==true)
                        for (i=0;i<strlen(strx);i++)
                            if (strx[i]<48 || strx[i]>57)
                            {
                                vis=false;
                                break;
                            }
                    if (vis==true)
                        for (i=0;i<strlen(stry);i++)
                            if (stry[i]<48 || stry[i]>57)
                            {
                                vis=false;
                                break;
                            }
                    if (vis==true)
                        for (i=0;i<strlen(strz);i++)
                            if (strz[i]<48 || strz[i]>57)
                            {
                                vis=false;
                                break;
                            }

                    if (vis==false)
                        SetWindowText(hLabTip,TEXT("��������ȷ�������"));
                    else
                    {
                        vis=false;
                        sx=atoi(strx);
                        sy=atoi(stry);
                        sz=atoi(strz);
                        if (info[sx][sy][sz].vis==false)
                            SetWindowText(hLabTip,TEXT("�÷��䲻����"));
                        else if (info[sx][sy][sz].vis==true && info[sx][sy][sz].use==true)
                            SetWindowText(hLabTip,TEXT("�÷����ѱ�������ѡ����������"));
                        else
                        {
                            SetWindowText(hLabTip,TEXT("�÷���ɹ�����ס"));
                            vis=true;
                        }
                    }

                    break;
                //�û��ύ
                case 13:

                    if (vis==false)
                    {
                        MessageBox(NULL,TEXT("��ѡ�񷿼�"),TEXT("��ʾ"),MB_OK);
                        break;
                    }

                    char name[100];
                    GetWindowText(hEditName,name,100);
                    if (strlen(name)==0)
                    {
                        MessageBox(NULL,TEXT("����������"),TEXT("��ʾ"),MB_OK);
                        break;
                    }

                    GetWindowText(hEditAge,strx,5);
                    int age=atoi(strx);
                    if (age<=0 || age>150)
                    {
                        MessageBox(NULL,TEXT("����д����"),TEXT("��ʾ"),MB_OK);
                        break;
                    }

                    int sex;
                    for (sex=4;sex<=6;sex++)
                        if (IsDlgButtonChecked(hwnd,sex)==BST_CHECKED)
                            break;

                    info[sx][sy][sz].use=true;
                    strcpy(info[sx][sy][sz].name,name);
                    info[sx][sy][sz].age=age;
                    info[sx][sy][sz].sex=sex-4;

                    SYSTEMTIME Time;
                    GetLocalTime(&Time);
                    info[sx][sy][sz].YY=Time.wYear;
                    info[sx][sy][sz].MM=Time.wMonth;
                    info[sx][sy][sz].DD=Time.wDay;
                    info[sx][sy][sz].hh=Time.wHour;
                    info[sx][sy][sz].mm=Time.wMinute;
                    info[sx][sy][sz].ss=Time.wSecond;

                    sprintf(szTextBuf,TEXT(" ������%s   ���䣺%ld   �Ա�%s \n ����ȼ���%ld   �����ţ�%ld   ��λ��ţ�%ld \n ����ʱ�䣺%04ld/%02ld/%02ld-%02ld:%02ld:%02ld \n ��ӭ������ס\n"),name,age,GetSex[sex-4],sx,sy,sz,info[sx][sy][sz].YY,info[sx][sy][sz].MM,info[sx][sy][sz].DD,info[sx][sy][sz].hh,info[sx][sy][sz].mm,info[sx][sy][sz].ss);
                    MessageBox(NULL,szTextBuf,TEXT("��Ϣ"),MB_OK);

                    MessageBox(NULL,notice,TEXT("��ʾ"),MB_OK);
                    //�޸���Ϣ
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)12,NULL);
                    break;

            }
            break;

        //���ڻ�����Ϣ
        case WM_PAINT:
            switch(wParam)
            {
                case 0:
                    //������
                    hdc=BeginPaint(hwnd,&ps);
                    SetTextColor(hdc,RGB(0,255,180));
                    SelectObject(hdc,hFontMainTitle);
                    //SetTextFont
                    rect.left=0;
                    rect.top=0;
                    rect.right=800;
                    rect.bottom=100;
                    DrawText(
                        hdc,
                        TEXT("��Ϣ��д"),
                        -1,
                        &rect,
                        DT_SINGLELINE | DT_CENTER | DT_VCENTER
                    );
                    EndPaint(hwnd,&ps);

                    //ͼƬ
                    GetModuleFileName(NULL,filename,300);
                    *(strstr(filename,"exe")-30)='\0';
                    strcat(filename,"Garden_Hotel.bmp");    //just bmp

                    hdc=GetDC(hwnd);
                    mdc=CreateCompatibleDC(hdc);
                    bg=(HBITMAP)LoadImage(
                        NULL,
                        filename,
                        IMAGE_BITMAP,
                        268,265,
                        LR_LOADFROMFILE
                    );
                    SelectObject(mdc,bg);
                    BitBlt(hdc,460,420,268,265,mdc,0,0,SRCAND);
                    break;
            }
            break;

        //����������Ϣ
        case WM_DESTROY:
            //������Ϣ
            print();
            SetTimer(NULL,0,300,TimerProc1);
            //����ʹ��MessageBoxTimeOut
            MessageBox(NULL,TEXT("��ӭ���ٴι���"),TEXT("���ݻ�԰�Ƶ�"),MB_OK);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
{
    SYSTEMTIME Time;
    TCHAR szTextBuf[100];

    GetLocalTime(&Time);
    sprintf(szTextBuf,"%04ld/%02ld/%02ld-%02ld:%02ld:%02ld",Time.wYear,Time.wMonth,Time.wDay,Time.wHour,Time.wMinute,Time.wSecond);
    SetWindowText(hLabTime,szTextBuf);
}

void CALLBACK TimerProc1(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
{
    exit(0);
}

void init()
{
    long x,y,z;
    for (x=1;x<=maxx;x++)
        for (y=1;y<=maxy;y++)
            for (z=1;z<=maxz;z++)
                info[x][y][z].vis=false;
    FILE *in=fopen("Room.txt","r");
    while (!feof(in))
    {
        fscanf(in,"%ld%ld%ld",&x,&y,&z);
        info[x][y][z].vis=true;
        info[x][y][z].use=false;
    }
    fclose(in);

    in=fopen("User.txt","r");
    while (!feof(in))
    {
        //room_grade room_number bed_number
        //name
        //age sex yy mm dd
        fscanf(in,"%ld%ld%ld",&x,&y,&z);
        info[x][y][z].use=true;
        fgets(info[x][y][z].name,100,in);
        info[x][y][z].name[strlen(info[x][y][z].name)-1]='\0';  //ɾȥ'\n'
        fscanf(in,"%ld%ld%ld%ld%ld%ld%ld%ld",&info[x][y][z].age,&info[x][y][z].sex,&info[x][y][z].YY,&info[x][y][z].MM,&info[x][y][z].DD,&info[x][y][z].hh,&info[x][y][z].mm,&info[x][y][z].ss);
    }
    fclose(in);
}

void print()
{
    long x,y,z;
    FILE *out1=fopen("Room.txt","w");
    FILE *out2=fopen("User.txt","w");
    //��Щ������ά�޹رգ�������ĳЩ����
    for (x=1;x<=maxx;x++)
        for (y=1;y<=maxy;y++)
            for (z=1;z<=maxz;z++)
                if (info[x][y][z].vis==true)
                {
                    fprintf(out1,"%ld %ld %ld\n",x,y,z);
                    if (info[x][y][z].use==true)
                    {
                        fprintf(out2,"%ld %ld %ld\n",x,y,z);
                        fprintf(out2,"%s\n",info[x][y][z].name);    //name����û�л��з���Ҫ����
                        fprintf(out2,"%ld %ld %ld %ld %ld %ld %ld %ld\n\n",info[x][y][z].age,info[x][y][z].sex,info[x][y][z].YY,info[x][y][z].MM,info[x][y][z].DD,info[x][y][z].hh,info[x][y][z].mm,info[x][y][z].ss);
                    }
                }
    fclose(out1);
    fclose(out2);
}
