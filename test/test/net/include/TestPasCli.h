#pragma once
#include "UvTcpCli.h"
class CTestPasCli : public CUvTcpCli
{
public:
	CTestPasCli();
	~CTestPasCli();

public:
	bool IsClose() { return mbClose; }

protected:
	int OnRecv(ssize_t nRead, const uv_buf_t* pBuf);
	int OnConn(int iStatus);
	int OnClose();
	int OnSend(int iStatus);
	int OnInit();

private:
	bool mbClose;
};

