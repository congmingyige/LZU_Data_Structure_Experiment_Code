#include <windows.h>

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    int nSelect=MessageBox(NULL,TEXT("Hello"),TEXT("welcome"),MB_OKCANCEL | MB_ICONINFORMATION);
    if (nSelect==IDOK)
    {
        MessageBox(NULL,TEXT("you choose yes"),TEXT("1"),MB_OK);
    }
    else
    {
        MessageBox(NULL,TEXT("you choose no"),TEXT("2"),MB_OK);
    }
    return 0;
}
