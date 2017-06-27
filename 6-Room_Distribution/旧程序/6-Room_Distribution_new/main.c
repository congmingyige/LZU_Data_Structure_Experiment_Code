#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#define maxn 100000
#define maxx 100
#define maxy 1000
#define maxz 10

struct node
{
    char name[50];
    long age;
    long sex;
    long yy,mm,dd;
    long grade;
    long room_number;
    long bed_number;
}*info[maxn+1];

long amount[maxx+1][maxy+1],f[maxx+1][maxy+1][maxz+1];
bool vis[maxx+1][maxy+1][maxz+1];

//���ڻ���
long stack[maxn+1],sum;




/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC         hdc;  //�豸�������
    PAINTSTRUCT ps;
    RECT        rect;

    switch (message){
        //���ڻ�����Ϣ
        case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps) ;
            GetClientRect (hwnd, &rect) ;
            DrawText(
                hdc,
                TEXT("��ã���ӭ����C����������"),
                -1,
                &rect,
                DT_SINGLELINE | DT_CENTER | DT_VCENTER
            );
            EndPaint (hwnd, &ps) ;
            return 0 ;

        //����������Ϣ
        case WM_DESTROY:
            PostQuitMessage(0) ;
            return 0 ;
    }
    return DefWindowProc(hwnd, message, wParam, lParam) ;
}

void Properties()
{
    long i,j,x,y,z;
    char c;
    for (i=1;i<=maxx+1;i++)
        for (j=1;j<=maxy+1;j++)
            amount[i][j]=-1;

    FILE *in=fopen("Properties.csv","r");
    while ()
    {
        //fscanf("%ld%c%ld%c%ld",&x,&c,&y,&c,&z)
        amount[x][y]=z;
        for (j=1;j<=z;j++)
            vis[x][y][z]=false;
    }
    fclose(in);
}

//void load()
//{
//    FILE *in=fopen("info.txt","r");
//    while (fscanf("%s%ld%ld%ld%ld%ld%ld"))
//    fclose(in);
//}

//void clsinfo()
//{
//    sum=0;
//}

void User()
{
    //printf("Please input ");
}

void Employee()
{

}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    long mode_person;
    FILE *out=fopen("info.txt","w");
    Properties();
//    load();
    while (1)
    {
        system("cls");
        printf("1:  User\n");
        printf("2:  Employee\n");
        switch(mode_person)
        {
            case 1:
                User();
            case 2:
                Employee();
            default:
                break;
        }
    }




    static TCHAR szClassName[] = TEXT("HelloWin");  //��������
    HWND     hwnd;  //���ھ��
    MSG      msg;  //��Ϣ
    WNDCLASS wndclass;  //������

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
