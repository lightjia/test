#include "TestSvr.h"

CTestSvr::CTestSvr(){
	mpTcpSvr = &mstTcpSvr;
	mpPasCli = NULL;
	mpMyLoop = new CUvLoop();
	mpMyLoop->StartLoop();
	miStep = 0;
	mpCliTcp = NULL;
	REF(this);
	SetUvLoop(uv_default_loop());
}

CTestSvr::~CTestSvr(){
}

int CTestSvr::UvCallBack(uv_loop_t* pLoop, void* pData) {
	ASSERT_RET_VALUE(pLoop && pData, 1);
	LOG_INFO("Enter CTestSvr::UvCallBack miStep:%d", miStep);
	if (miStep == 0) {
		uv_tcp_t* pCliTcp = (uv_tcp_t*)MemMalloc(sizeof(uv_tcp_t));
		uv_tcp_init(pLoop, pCliTcp);
		mpCliTcp = pCliTcp;
		miStep = 1;
	}

	if (mpPasCli && miStep == 1) {
		mpPasCli->SetUvLoop(pLoop);
		mpPasCli->SetTcpCli(mpCliTcp);
		mpPasCli->Init();
		mpCliTcp = NULL;
		miStep = 0;
	}
	return 0;
}

uv_tcp_t* CTestSvr::AllocTcpCli() {
	LOG_INFO("Enter CTestSvr::AllocTcpCli:%s", GetNetId().c_str());
	ASSERT_RET_VALUE(!mpCliTcp, mpCliTcp);
	mpMyLoop->CallUv(this, (void*)&miStep);
	while (!mpCliTcp) {
		sleep_ms(10);
	}

	return mpCliTcp;
}

int CTestSvr::OnAccept(uv_tcp_t* pUvTcp) {
	if (pUvTcp) {
		mpPasCli = new CTestPasCli();
		LOG_INFO("Enter CTestSvr::OnAccept:%s", mpPasCli->GetNetId().c_str());
		mpMyLoop->CallUv(this, (void*)&miStep);
		while (1 == miStep) {
			sleep_ms(10);
		}

		mvecClis.push_back(mpPasCli);
		mpPasCli = NULL;
	}

	for (std::vector<CTestPasCli*>::iterator iter = mvecClis.begin(); iter != mvecClis.end();) {
		CTestPasCli* pCli = *iter;
		if (pCli->IsClose()) {
			DODELETE(pCli);
			iter = mvecClis.erase(iter);
		} else {
			++iter;
		}
	}
	return 0;
}

int CTestSvr::OnInit() {
	return Listen();
}