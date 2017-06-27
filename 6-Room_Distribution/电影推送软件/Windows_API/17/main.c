#include <windows.h>
#include <stdio.h>

char weekname[7][5]={"日","一","二","三","四","五","六"};

int main( void )
{
SYSTEMTIME sys;
GetLocalTime( &sys );
printf( "%4d/%02d/%02d %02d:%02d:%02d 星期%s\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,weekname[sys.wDayOfWeek]);
return 0;
}
