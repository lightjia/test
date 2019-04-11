// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CLogmanager.h"
#include "RandTool.h"
#include "UvUtil.h"
#include "MemMgr.h"
#include "UvTaskPool.h"
#include "MemTest.h"
#include "ClassMem.h"
int main(){
	sMemMgr->SetAlign(100);
	sMemMgr->SetAllocMinLimit(0);
//	printf("=======%lld=====\n", sMemMgr->GetTotalMem());
//	CClassMem* pClass = new CClassMem();
//	printf("=======%lld=====\n", sMemMgr->GetTotalMem());
	sLog->Init(2, 5, ".");
	sLog->SetMemOperFunc(MEMMGR_MEM_FUNC);
	sUvTaskPool->Init();
	for (int i = 0; i <= 600; ++i) {
		CMemTest* pTest = new CMemTest(i);
		REF(pTest);
		pTest->SetMemOperFunc(MEMMGR_MEM_FUNC);
		sUvTaskPool->PushTask(pTest);
		UNREF(pTest);
	}

	LOG_INFO("Current Use Mem:%lld", sMemMgr->GetTotalMem());
	sleep_ms(1000 * 60 * 15);
	for (int i = 1001; i <= 2000; ++i) {
		CMemTest* pTest = new CMemTest(i);
		REF(pTest);
		sUvTaskPool->PushTask(pTest);
		UNREF(pTest);
	}

	while (true) {
		sleep_ms(sRandTool->RandInt(1000, 3000));
	}

    return 0;
}
