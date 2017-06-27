
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

     // TODO: Place code here.
    MSG msg;
    HACCEL hAccelTable;

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, (LPWSTR)custommessage.commonvariables.szTitle.c_str(), MAX_LOADSTRING);
    LoadString(hInstance, IDS_APP_TITLE, (LPWSTR)custommessage.commonvariables.szWindowClass.c_str(), MAX_LOADSTRING);

    custommessage.commonvariables.hInst = hInstance; // Store instance handle in our global variable

    custommessage.commonvariables.hMainWnd = CreateDialog(custommessage.commonvariables.hInst, MAKEINTRESOURCE(IDD_DIALOG_WNDPROC), 0, (DLGPROC)WndProc);
    if (!custommessage.commonvariables.hMainWnd)
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDM_MENU_CWINDOW));
    ShowWindow(custommessage.commonvariables.hMainWnd, nCmdShow);

    // Main message loop:

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (msg.hwnd == 0 ||  !IsDialogMessage (msg.hwnd, &msg))
        {
            if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        {
            custommessage.InitializationWndprocControl(hWnd);  // 控件初始化
        }
        break;
    case WM_COMMAND:
        {
            custommessage.commonvariables.wmId    = LOWORD(wParam);
            custommessage.commonvariables.wmEvent = HIWORD(wParam);
            // Parse the menu selections:
            switch(custommessage.commonvariables.wmId)
            {
            case IDB_WNDPROC_SEARCHALLDLGDOWN:
                {
                    custommessage.commonvariables.hSearchWnd = CreateDialog(custommessage.commonvariables.hInst, MAKEINTRESOURCE(IDD_DIALOG_ALLSEARCH), 0, (DLGPROC)AllsearchProc);  // hWnd也不成
                    ShowWindow(custommessage.commonvariables.hSearchWnd, SW_SHOW);
                }
                break;
            case IDM_EXIT:
                {
                    DestroyWindow(hWnd);
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            custommessage.commonvariables.hdc = BeginPaint(hWnd, &custommessage.commonvariables.ps);
            // TODO: Add any drawing code here...
            EndPaint(hWnd, &custommessage.commonvariables.ps);
        }
        break;
    case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK AllsearchProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        {
            custommessage.InitializationSearchControl(hWnd);  // 控件初始化
        }
        break;
    case WM_COMMAND:
        {
            custommessage.commonvariables.wmId    = LOWORD(wParam);
            custommessage.commonvariables.wmEvent = HIWORD(wParam);
            SetFocus(hWnd);
            // Parse the menu selections:
            switch(custommessage.commonvariables.wmId)
            {
            case IDB_SEARCH_ALLSEARCH:
                {
                    DestroyWindow(hWnd);
                    hWnd = NULL;
                }
                break;
            default:
                return FALSE;
            }
        }
        break;
    case WM_PAINT:
        {
            custommessage.commonvariables.hdc = BeginPaint(hWnd, &custommessage.commonvariables.ps);
            // TODO: Add any drawing code here...
            EndPaint(hWnd, &custommessage.commonvariables.ps);
        }
        break;
    case WM_SYSCOMMAND:
        {
            if(wParam == SC_CLOSE)
            {
                DestroyWindow(hWnd);
                hWnd = NULL;
            }
        }
        break;
    case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;
    default:
        return FALSE;  // 未处理的消息
    }
    return TRUE;  // 处理过的消息
}
