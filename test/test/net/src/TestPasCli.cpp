#include "TestPasCli.h"

CTestPasCli::CTestPasCli(){
	mbClose = false;
}

CTestPasCli::~CTestPasCli(){
}

int CTestPasCli::OnRecv(ssize_t nRead, const uv_buf_t* pBuf) {
	if (nRead > 0 && pBuf && pBuf->base) {
		pBuf->base[nRead] = '\0';
		LOG_INFO("Cli:%d Recv:%s", GetPort(), pBuf->base);
		Send(pBuf->base, nRead);
	}
	return 0;
}

int CTestPasCli::OnConn(int iStatus) {
	if (!iStatus) {
		char* pBuf = "Hello I Am Svr";
		Send(pBuf, strlen(pBuf));
	}
	
	return 0;
}

int CTestPasCli::OnClose() {
	mbClose = true;
	return 0;
}

int CTestPasCli::OnSend(int iStatus) {
	return 0;
}

int CTestPasCli::OnInit() {
	return 0;
}