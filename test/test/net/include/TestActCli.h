#pragma once
#include "UvTcpCli.h"
class CTestActCli : public CUvTcpCli{
public:
	CTestActCli();
	~CTestActCli();

protected:
	int OnRecv(ssize_t nRead, const uv_buf_t* pBuf);
	int OnConn(int iStatus);
	int OnClose();
	int OnSend(int iStatus);
	int OnInit();

private:
	uv_tcp_t mstTcpCli;
	uv_connect_t mstUvConn;
};

