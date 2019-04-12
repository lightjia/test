#include "TestActCli.h"

CTestActCli::CTestActCli() {
	SetUvLoop(uv_default_loop());
	mpTcpCli = &mstTcpCli;
	mpUvConn = &mstUvConn;
}

CTestActCli::~CTestActCli(){
}

int CTestActCli::OnRecv(ssize_t nRead, const uv_buf_t* pBuf) {
	if (nRead > 0 && pBuf && pBuf->base) {
		pBuf->base[nRead] = '\0';
		LOG_INFO("Cli:%d Recv:%s", GetPort(), pBuf->base);
		char buf[100];
		snprintf(buf, 100, "Hello Svr I am %d", GetPort());
		Send(buf, strlen(buf));
	}

	return 0;
}

int CTestActCli::OnConn(int iStatus) {
	return 0;
}

int CTestActCli::OnClose() {
	LOG_INFO("Cli:%d Close", GetPort());
	return 0;
}

int CTestActCli::OnSend(int iStatus) {
	return 0;
}

int CTestActCli::OnInit() {
	return 0;
}