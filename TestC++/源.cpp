#pragma once
#include <vector>
#include <algorithm>
#include <TestC++Dll/TestC++Dll.h>

#include<Windows.h>
#include<DbgHelp.h>
#pragma comment(lib,"DbgHelp.lib")

LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
    HANDLE hFile = CreateFile("mini.dmp", GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
        return EXCEPTION_EXECUTE_HANDLER;

    MINIDUMP_EXCEPTION_INFORMATION mdei;
    mdei.ThreadId = GetCurrentThreadId();
    mdei.ExceptionPointers = ExceptionInfo;
    mdei.ClientPointers = NULL;
    MINIDUMP_CALLBACK_INFORMATION mci;
    mci.CallbackRoutine = NULL;
    mci.CallbackParam = 0;

    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &mdei, NULL, &mci);

    CloseHandle(hFile);
    return EXCEPTION_EXECUTE_HANDLER;
}
//int crashtest(int a, int b)
//{
//    int c;
//    c = a / b;
//    return c;
//}
int main(int argc, char *argv[])
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)MyUnhandledExceptionFilter);
    int a = 30;
    int b = 0;
    int ret;
    printf("let's begin crash test...n");
    ret = crashtest(a, b);
    getchar();
    return 0;
}