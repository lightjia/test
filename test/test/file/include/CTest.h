#pragma once
#include "UvThread.h"
#include "UvMutex.h"
class CTest :
    public CUvThread
{
public:
    CTest();
    ~CTest();

protected:
    int OnThreadRun();

private:
    static int iIndex;
    static CUvMutex mcMutex;
    int miIndex;
};

