#include "TestActCli.h"

CTestActCli::CTestActCli() {
	SetUvLoop(uv_default_loop());
	mpTcpCli = &mstTcpCli;
	mpUvConn = &mstUvConn;
	mbConn = false;
	miLastSend = 0;
}

CTestActCli::~CTestActCli(){
}

void CTestActCli::OnBaseTimer(){
	if (!mbConn) {
		Connect("192.168.2.101", 7878);
		mbConn = true;
	}else {
		size_t iBufLen = 190;
		char* pBuf = (char*)MemMalloc(iBufLen);
		for (size_t i = 0; i < iBufLen; ++i) {
			pBuf[i] = 'a' + i % 26;
		}

		Send(pBuf, iBufLen);
		MemFree(pBuf);
	}
}

int CTestActCli::OnRecv(ssize_t nRead, const uv_buf_t* pBuf) {
	if (nRead > 0 && pBuf && pBuf->base) {
		pBuf->base[nRead - 1] = '\0';
		LOG_INFO("Cli:%d Recv:%s", GetPort(), pBuf->base);
	}

	return 0;
}

int CTestActCli::OnConn(int iStatus) {
	LOG_INFO("Conn REsult:%d", iStatus);

	return 0;
}

int CTestActCli::OnClose() {
	LOG_INFO("Cli:%d Close", GetPort());
	return 0;
}

int CTestActCli::OnSend(int iStatus) {
	LOG_INFO("CTestActCli %s %d Send:%ld NeedSend:%ld Recv:%ld", GetNetId().c_str(), GetTotalSendBytes(), GetNeedSendBytes(), GetTotalRecvBytes());
	return 0;
}

int CTestActCli::OnInit() {
	return StartBaseTimer(1000, 1000);
}