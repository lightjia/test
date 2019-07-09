#pragma once
#include "Task.h"
#include "Log.h"
#include "RandTool.h"
#include "MemMgr.h"
class CTestTasks : public CTask, public CMemOper
{
public:
	CTestTasks();
	~CTestTasks();

public:
	int TaskInit();
	int TaskExcute();
	int TaskQuit();
};

