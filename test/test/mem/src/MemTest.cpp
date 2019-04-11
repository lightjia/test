#include "MemTest.h"

CMemTest::CMemTest(int iId){
	miID = iId;
}

CMemTest::~CMemTest(){
}

int CMemTest::TaskInit() {
	miTime = get_time_ms();
	LOG_INFO("Task id:%d Statrt:%lld", miID, miTime);
	return 0;
}

int CMemTest::TaskExcute() {
	for (int i = 0; i < 10000; ++i) {
		uint64_t iTmp = get_time_ms();
		int iMemSize = sRandTool->RandInt(1, 10000);
		void* pData = MemMalloc(iMemSize);
		int iUse = (int)(get_time_ms() - iTmp);
		if (iUse > 0) {
			LOG_INFO("Task:%d Malloc Use:%d iMemSize:%d", miID, iUse, iMemSize);
		}
		
		int iSleepMs = sRandTool->RandInt(1, 10);
		sleep_ms(iSleepMs);
		iTmp = get_time_ms();
		MemFree(pData);
		iUse = (int)(get_time_ms() - iTmp);
		if (iUse > 0) {
			LOG_INFO("Task:%d Free Use:%d iMemSize:%d iSleepMs:%d", miID, iUse, iMemSize, iSleepMs);
		}
	}
	return 0;
}

int CMemTest::TaskQuit() {
	uint64_t iOff = get_time_ms() - miTime;
	LOG_INFO("Task id:%d End:%lld", miID, iOff);
	return 0;
}