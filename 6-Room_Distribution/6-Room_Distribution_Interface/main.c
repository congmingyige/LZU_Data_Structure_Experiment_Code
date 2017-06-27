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
    //vis=tree代表该房间可以被使用
    bool vis;
    //use=tree代表该房间正在被使用
    bool use;
    char name[maxlen+1];
    //0:男，1:女，2:不填
    long age;
    long sex;
    long YY,MM,DD,hh,mm,ss;
//    long room_grade;
//    long room_number;
//    long bed_number;
}info[maxx+1][maxy+1][maxz+1];
char notice[1000]="尊敬的宾客  Dear customers (patrons)\n为了您的健康和安全，请不要在客房进行黄赌毒。\nFor the sake of your health and safety, please do not gamble,take drugs, or take part in vice activities  (in prostitution)\n为了您的财产安全，请自行妥善保管好您随身的贵重物品，\nFor the sake of safe custody of your valuables or own belongings\n如有遗失，本酒店概不负责！\nThis hotel bears no responsibility for any losses.\n当您需要酒店服务时，请直接拨打总机号码“0”，我们随时为您服务！\nPlease dial \"0\" when you require our services. We are always happy to serve you.\n\n预祝您在广州花园酒店住得舒适\n";
char GetSex[3][6]={"男","女","未填写"};

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
    static TCHAR szClassName[] = TEXT("HelloWin");  //窗口类名
    HWND hwnd;  //窗口句柄
    HFONT hFontNumber;
    MSG msg;  //消息
    WNDCLASS wndclass;  //窗口类

    /**********第①步：注册窗口类**********/
    //为窗口类的各个字段赋值
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //窗口风格
    wndclass.lpfnWndProc  = WndProc;  //窗口过程
    wndclass.cbClsExtra   = 0;  //暂时不需要理解
    wndclass.cbWndExtra   = 0;  //暂时不需要理解
    wndclass.hInstance    = hInstance;  //当前窗口句柄    //应该是用于区分不同窗口，从而在下面的程序中在不同窗口执行不同语句  hwnd.hInstance???
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //窗口图标
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW);  //鼠标样式
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);  //窗口背景画刷
    wndclass.lpszMenuName = NULL ;  //窗口菜单
    wndclass.lpszClassName= szClassName;  //窗口类名

    //注册窗口
    RegisterClass(&wndclass);

    /*****第②步：创建窗口(并让窗口显示出来)*****/
    hwnd = CreateWindow(
        szClassName,  //窗口类的名字
        TEXT("欢迎入住广州花园酒店 —— 网络订房"),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        400,  //初始化时x轴的位置
        15,  //初始化时y轴的位置
        800,  //窗口宽度
        800,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );

    //显示窗口
    ShowWindow(hwnd,SW_SHOW);
    //更新（绘制）窗口
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

    SetTimer(hwnd,1,1000,TimerProc);                //时间显示
    SendMessage(hwnd,WM_PAINT,(WPARAM)0,NULL);      //文字和图片显示

    /**********第③步：消息循环**********/
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage (&msg);  //分派消息
    }

    return msg.wParam;
}

/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC         hdc;  //设备环境句柄
    PAINTSTRUCT ps;
    RECT        rect;
    HDC mdc;
    HBITMAP bg;
    LOGFONT logFont;
    static HBRUSH hBrush;
    INT wmId,wmEvent;   //用了这两个后可以接收修改edit发给WM_COMMAND的信息
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
        //刚创建时执行WM_CREATE,以后不再执行
        case WM_CREATE:
            //创建字体
            hFontTitle=CreateFont(
                -22,-11,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("隶书")
            );

            hFontCh=CreateFont(
                -28,-14,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("黑体")
            );

            hFontMode=CreateFont(
                -18,-9,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("楷体")
            );

            hFontMainTitle=CreateFont(
                -30,-15,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("华文行楷")
            );

            hLabName=CreateWindow(
                TEXT("static"),TEXT("姓名"),
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
                TEXT("static"),TEXT("年龄"),
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
                TEXT("static"),TEXT("性别"),
                WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | SS_CENTERIMAGE,
                280,160,90,40,
                hwnd,(HMENU)3,hInst,NULL
            );

            checkboxMale=CreateWindow(
                TEXT("button"),TEXT("男"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                390,167,40,26,
                hwnd,(HMENU)4,hInst,NULL
            );

            checkboxFemale=CreateWindow(
                TEXT("button"),TEXT("女"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                440,167,40,26,
                hwnd,(HMENU)5,hInst,NULL
            );

            checkboxNoneSex=CreateWindow(
                TEXT("button"),TEXT("不填"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                490,167,65,26,
                hwnd,(HMENU)6,hInst,NULL
            );

            //改变checkbox的checked状态
            CheckDlgButton(hwnd,6,1);

            hLabRoomLevel=CreateWindow(
                TEXT("static"),TEXT("客房等级"),
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
                TEXT("static"),TEXT("房间号"),
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
                TEXT("static"),TEXT("床位号"),
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
                TEXT("button"),TEXT("提交"),
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
            SetWindowText(hLabTip,TEXT("请输入完整房间号码"));

            //???
            hLabAdd=CreateWindow(
                TEXT("static"),TEXT("添加"),
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
                TEXT("button"),TEXT("确定"),
                WS_CHILD | WS_BORDER | BS_CENTER | BS_VCENTER,
                380,200,80,40,
                hwnd,(HMENU)19,hInst,NULL
            );

            hLabDel=CreateWindow(
                TEXT("static"),TEXT("删除"),
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
                TEXT("button"),TEXT("确定"),
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
            wmEvent=HIWORD(wParam); //用了这两个后可以接收修改edit发给WM_COMMAND的信息
            switch (wmId)
            {
//                case 2:
//                    GetWindowText(hEditName,szTextBuf,100);
//                    if (strcmp(szTextBuf,"AdminGardenHotel")==0)
//                    {
//                        //MessageBox.show("请输入{0}的值", n);
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
                        SetWindowText(hLabTip,TEXT("请输入正确房间号码"));
                    else
                    {
                        vis=false;
                        sx=atoi(strx);
                        sy=atoi(stry);
                        sz=atoi(strz);
                        if (info[sx][sy][sz].vis==false)
                            SetWindowText(hLabTip,TEXT("该房间不存在"));
                        else if (info[sx][sy][sz].vis==true && info[sx][sy][sz].use==true)
                            SetWindowText(hLabTip,TEXT("该房间已被订，请选择其它房间"));
                        else
                        {
                            SetWindowText(hLabTip,TEXT("该房间可供您入住"));
                            vis=true;
                        }
                    }

                    break;
                //用户提交
                case 13:

                    if (vis==false)
                    {
                        MessageBox(NULL,TEXT("请选择房间"),TEXT("提示"),MB_OK);
                        break;
                    }

                    char name[100];
                    GetWindowText(hEditName,name,100);
                    if (strlen(name)==0)
                    {
                        MessageBox(NULL,TEXT("请输入姓名"),TEXT("提示"),MB_OK);
                        break;
                    }

                    GetWindowText(hEditAge,strx,5);
                    int age=atoi(strx);
                    if (age<=0 || age>150)
                    {
                        MessageBox(NULL,TEXT("请填写年龄"),TEXT("提示"),MB_OK);
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

                    sprintf(szTextBuf,TEXT(" 姓名：%s   年龄：%ld   性别：%s \n 房间等级：%ld   房间编号：%ld   床位编号：%ld \n 订房时间：%04ld/%02ld/%02ld-%02ld:%02ld:%02ld \n 欢迎您的入住\n"),name,age,GetSex[sex-4],sx,sy,sz,info[sx][sy][sz].YY,info[sx][sy][sz].MM,info[sx][sy][sz].DD,info[sx][sy][sz].hh,info[sx][sy][sz].mm,info[sx][sy][sz].ss);
                    MessageBox(NULL,szTextBuf,TEXT("信息"),MB_OK);

                    MessageBox(NULL,notice,TEXT("提示"),MB_OK);
                    //修改信息
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)12,NULL);
                    break;

            }
            break;

        //窗口绘制消息
        case WM_PAINT:
            switch(wParam)
            {
                case 0:
                    //主标题
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
                        TEXT("信息填写"),
                        -1,
                        &rect,
                        DT_SINGLELINE | DT_CENTER | DT_VCENTER
                    );
                    EndPaint(hwnd,&ps);

                    //图片
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

        //窗口销毁消息
        case WM_DESTROY:
            //保存信息
            print();
            SetTimer(NULL,0,300,TimerProc1);
            //不能使用MessageBoxTimeOut
            MessageBox(NULL,TEXT("欢迎您再次光临"),TEXT("广州花园酒店"),MB_OK);
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
        info[x][y][z].name[strlen(info[x][y][z].name)-1]='\0';  //删去'\n'
        fscanf(in,"%ld%ld%ld%ld%ld%ld%ld%ld",&info[x][y][z].age,&info[x][y][z].sex,&info[x][y][z].YY,&info[x][y][z].MM,&info[x][y][z].DD,&info[x][y][z].hh,&info[x][y][z].mm,&info[x][y][z].ss);
    }
    fclose(in);
}

void print()
{
    long x,y,z;
    FILE *out1=fopen("Room.txt","w");
    FILE *out2=fopen("User.txt","w");
    //有些房间因维修关闭，或增添某些房间
    for (x=1;x<=maxx;x++)
        for (y=1;y<=maxy;y++)
            for (z=1;z<=maxz;z++)
                if (info[x][y][z].vis==true)
                {
                    fprintf(out1,"%ld %ld %ld\n",x,y,z);
                    if (info[x][y][z].use==true)
                    {
                        fprintf(out2,"%ld %ld %ld\n",x,y,z);
                        fprintf(out2,"%s\n",info[x][y][z].name);    //name本来没有换行符，要加上
                        fprintf(out2,"%ld %ld %ld %ld %ld %ld %ld %ld\n\n",info[x][y][z].age,info[x][y][z].sex,info[x][y][z].YY,info[x][y][z].MM,info[x][y][z].DD,info[x][y][z].hh,info[x][y][z].mm,info[x][y][z].ss);
                    }
                }
    fclose(out1);
    fclose(out2);
}
