#include <windows.h>
#include <string.h>
long t=0;
    HWND hwnd1;  //���ھ��
    HWND hwnd2;


/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC         hdc;  //�豸�������
    PAINTSTRUCT ps;
    RECT        rect;

    ///��Ѵ��ڽ��У�����(�ƶ�����)�����ڵ�ֵ�ͻ�ı�;�����ڰ���ťҲ����
    t=(t+1)%10000000;
//    if (t%100==0)
//        ShowWindow (hwnd1, SW_HIDE);
//    else if (t%100==50)
//        ShowWindow (hwnd1, SW_SHOW);

    INT wmId,wmEvent;
    char szTextBuf[100];
    switch (message){
        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch (wmId)
            {
                case 1:
                    MessageBox(hwnd,TEXT("haha"),TEXT("���ֹ���"),MB_ICONINFORMATION);
                    break;
            }
            break;
        //���ڻ�����Ϣ
        case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps) ;
            GetClientRect (hwnd, &rect) ;
            sprintf(szTextBuf,TEXT("%ld"),t);
            DrawText(
                hdc,
                szTextBuf,
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

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    static TCHAR szClassName[] = TEXT("HelloWin");  //��������
    MSG      msg;  //��Ϣ
    WNDCLASS wndclass;  //������

    /**********�ڢٲ���ע�ᴰ����**********/
    //Ϊ������ĸ����ֶθ�ֵ
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //���ڷ��
    wndclass.lpfnWndProc  = WndProc;  //���ڹ��� !!!
    wndclass.cbClsExtra   = 0;  //��ʱ����Ҫ���
    wndclass.cbWndExtra   = 0;  //��ʱ����Ҫ���
    wndclass.hInstance    = hInstance;  //��ǰ���ھ�� !!!
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //����ͼ��
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW);  //�����ʽ
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);  //���ڱ�����ˢ
    wndclass.lpszMenuName = NULL ;  //���ڲ˵�
    wndclass.lpszClassName= szClassName;  //��������

    //ע�ᴰ��
    RegisterClass(&wndclass);

    /*****�ڢڲ�����������(���ô�����ʾ����)*****/
    hwnd1 = CreateWindow(
        szClassName,  //�����������
        TEXT("1"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        CW_USEDEFAULT,  //��ʼ��ʱx���λ��
        CW_USEDEFAULT,  //��ʼ��ʱy���λ��
        500,  //���ڿ��
        300,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����     ///�������ɷ����������û�д��ڲ˵�������ܹ��� (HMENU)1
        hInstance,  //��ǰ���ڵľ��   ///������hInstance�����Ըı䣬��Ϊ0��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow (hwnd1, iCmdShow);
    //���£����ƣ�����
    UpdateWindow (hwnd1);

    hwnd2 = CreateWindow(
        szClassName,  //�����������
        TEXT("2"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        200,  //��ʼ��ʱx���λ��
        100,  //��ʼ��ʱy���λ��
        500,  //���ڿ��
        300,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );
    ShowWindow (hwnd2, SW_SHOW);
    UpdateWindow (hwnd2);

    HWND name;
    name=CreateWindow(
                TEXT("button"),TEXT("a"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                10,20,60,30,
                hwnd1,(HMENU)1,hInstance,NULL   //�����ĸ����ھ�д����Ӵ��Ժ���ڸø�������
            );
    HWND age;
    age=CreateWindow(
                TEXT("static"),TEXT("b"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,100,120,40,
                hwnd2,(HMENU)2,hInstance,NULL
            );

    /**********�ڢ۲�����Ϣѭ��**********/
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage (&msg);  //������Ϣ
        switch(msg.message)
        {
            case WM_KEYDOWN:
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('1')<0)
                {
                    t++;
                }
                break;
        }
    }

    return msg.wParam;
}
