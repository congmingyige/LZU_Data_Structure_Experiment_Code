#include <windows.h>
#include <stdio.h>

char weekname[7][5]={"��","һ","��","��","��","��","��"};

int main( void )
{
SYSTEMTIME sys;
GetLocalTime( &sys );
printf( "%4d/%02d/%02d %02d:%02d:%02d ����%s\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,weekname[sys.wDayOfWeek]);
return 0;
}
