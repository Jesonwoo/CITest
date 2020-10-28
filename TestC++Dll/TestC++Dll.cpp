// TestC++Dll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "TestC++Dll.h"


int crashtest(int a, int b)
{
    int c;
    c = a / b;
    return c;
}

