// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Log.h"
#include "RandTool.h"
#include "UvUtil.h"
#include "MemMgr.h"
#include "UvTaskPool.h"
#include "MemTest.h"
#include "ClassMem.h"
#include "TestActCli.h"
#include "TestSvr.h"

void TestSvr(){
	CTestSvr* pSvr = new CTestSvr();
	pSvr->SetMemOperFunc(MEMMGR_MEM_FUNC);
	pSvr->SetNetParam("192.168.2.101", 7878);
	pSvr->Init();
}

void TestCli(int iNum) {
	for (int i = 0; i < iNum; ++i) {
		CTestActCli* pCli = new CTestActCli();
		pCli->SetMemOperFunc(MEMMGR_MEM_FUNC);
		pCli->Init();
	}
}

void logfile(const std::string& strLog) {
	printf("Current LogFile:%s\n", strLog.c_str());
}

int main(int argc, char* argv[]){
	/*sMemMgr->SetAlign(100);
	sMemMgr->SetAllocMinLimit(100);*/
	tagLogInitParam stLogParam;
	sLog->Init(stLogParam);
	//sLog->SetMemOperFunc(MEMMGR_MEM_FUNC);
	sUvTaskPool->Init();
	while (true) {
		sleep_ms(sRandTool->RandInt(100, 300));
		unsigned long iLen = 1024 * 1024 * 3;
		char* pData = (char*)do_malloc(iLen * sizeof(char));
		for (int i = 0; i < iLen - 1; ++i) {
			pData[i] = 'a' + i % 26;
		}
		pData[iLen - 1] = '\0';
		LOG_INFO("%s", pData);
	}

	int iCliNum = 1;
	bool bSvr = true;
	if (argc > 2) {
		bSvr = false;
		iCliNum = atoi(argv[2]);
		if (iCliNum <= 0) {
			iCliNum = 1;
		}
	}

	if (bSvr) {
		TestSvr();
	} else {
		TestCli(iCliNum);
	}
	
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	while (true) {
		sleep_ms(sRandTool->RandInt(1000, 3000));
	}

    return 0;
}