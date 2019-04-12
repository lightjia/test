#include "TestSvr.h"

CTestSvr::CTestSvr(){
	mpTcpSvr = &mstTcpSvr;
	SetUvLoop(uv_default_loop());
}

CTestSvr::~CTestSvr(){
}

int CTestSvr::OnAccept(uv_tcp_t* pUvTcp) {
	if (pUvTcp) {
		CTestPasCli* pCli = new CTestPasCli();
		pCli->SetUvLoop(GetUvLoop());
		pCli->SetTcpCli(pUvTcp);
		pCli->Init();
		mvecClis.push_back(pCli);
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