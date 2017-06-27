#include <stdio.h>
#include <wchar.h>
#include <string.h>

int main()
{
    char str[]="C中文网";
    wchar_t wstr[]=L"C中文网";
    printf("%d,%d\n",strlen(str),wcslen(wstr));
    return 0;
}
