#pragma once
#include "Task.h"
#include "MemOper.h"
#include "RandTool.h"
class CMemTest : public CTask, public CMemOper{
public:
	CMemTest(int iId);
	~CMemTest();

public:
	int TaskInit();
	int TaskExcute();
	int TaskQuit();

private:
	int miID;
	uint64_t miTime;
};