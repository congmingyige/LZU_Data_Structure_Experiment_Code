#include <stdio.h>
#include <wchar.h>
#include <string.h>

int main()
{
    char str[]="C������";
    wchar_t wstr[]=L"C������";
    printf("%d,%d\n",strlen(str),wcslen(wstr));
    return 0;
}
