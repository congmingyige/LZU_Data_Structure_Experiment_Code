#include <stdio.h>
#include <wchar.h>

int main()
{
    char ch='a';
    wchar_t wch='a';
    char str[]="������";
    wchar_t wstr[]= L"������";
    printf("ch=%d,wch=%d,str=%d,wstr=%d\n",sizeof(ch),sizeof(wch),sizeof(str),sizeof(wstr));
}
