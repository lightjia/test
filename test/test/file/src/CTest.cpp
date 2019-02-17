#include "CTest.h"
#include "CLogmanager.h"
#include "RandTool.h"
#include "Tmp.h"

int CTest::iIndex = 0;
CUvMutex CTest::mcMutex;

CTest::CTest()
{
//    CUvAutoMutex tmpMutex(&mcMutex);
    iIndex++;
    miIndex = iIndex;
}


CTest::~CTest()
{
}

int CTest::OnThreadRun() {
    if (iIndex <= 100) {
        CUvAutoMutex tmpMutex(&mcMutex);
        if (iIndex <= 100) {
            for (int i = 0; i < 1; ++i) {
                CTest* pTest = new CTest;
                pTest->Start();
            }
        }
    }

    int iLoop = sRandTool->RandInt(1000, 3000);
    int iTmp = 0;
    CTmp* pp = NULL;
    for (;;) {
        sleep_ms(sRandTool->RandInt(28, 40));
        if (iTmp++ <= iLoop) {
            if (sRandTool->RandInt(100, 300) > 200) {
                LOG_INFO("Hello Jia In:%d", miIndex);
                if (!pp) {
                    pp = new CTmp();
                }
                else {
                    DODELETE(pp);
                }
            } else {
                LOG_ERR("Hello Jia In:%d", miIndex);
            }
        } else {
            DODELETE(pp);
        }
    }
}
