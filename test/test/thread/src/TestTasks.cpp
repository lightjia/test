#include "..\include\TestTasks.h"

CTestTasks::CTestTasks():CMemOper(MEMMGR_MEM_FUNC)
{
}

CTestTasks::~CTestTasks()
{
}

int CTestTasks::TaskInit() {
	return 0;
}

int CTestTasks::TaskExcute() {
	int iMalloc = -1;
	int iFree = -1;
	_u64 iNum = 0;
	_u64 iMallocTime = 0;
	_u64 iFreeTime = 0;
	for (;;) {
		_u64 iNow = get_time_ms();
		iNum++;
		void* pData = MemMalloc(sRandTool->RandInt(1024, 30240));
		int iOff = (int)(get_time_ms() - iNow);
		iMallocTime += iOff;
		if (iMalloc < iOff) {
			LOG_INFO("MemMalloc Use:%d Ms iNum:%I64u iTime:%I64u aveg:%d", iOff, iNum, iMallocTime, (int)(iMallocTime / iNum));
			iMalloc = iOff;
		}
		iNow = get_time_ms();
		MemFree(pData);
		iOff = (int)(get_time_ms() - iNow);
		iFreeTime += iOff;
		if (iFree < iOff) {
			LOG_INFO("MemFree Use:%d Ms iNum:%I64u iTime:%I64u aveg:%d", iOff, iNum, iFreeTime, (int)(iFreeTime / iNum));
			iFree = iOff;
		}

		sleep_ms(sRandTool->RandInt(1, 10));
	}
	return 0;
}

int CTestTasks::TaskQuit() {
	return 0;
}