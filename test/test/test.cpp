// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CLogmanager.h"
#include "CTest.h"
int main()
{
    sLog->Init(2, 5, ".");
    CTest* pTest = new CTest;
    pTest->Start();

    for (;;) {
        LOG_INFO("Hello Jia");
        sleep_ms(1000);
    }
    return 0;
}