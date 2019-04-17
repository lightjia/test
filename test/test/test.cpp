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

int main(int argc, char* argv[]){
	sMemMgr->SetAlign(100);
	sMemMgr->SetAllocMinLimit(100);
	sLog->Init(2, 5, ".");
	sLog->SetMemOperFunc(MEMMGR_MEM_FUNC);
	sUvTaskPool->Init();

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