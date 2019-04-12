#pragma once
#include "UvTcpSvr.h"
#include "TestPasCli.h"
#include <vector>
class CTestSvr : public CUvTcpSvr{
public:
	CTestSvr();
	~CTestSvr();

public:
	int OnAccept(uv_tcp_t* pUvTcp);
	int OnInit();

private:
	uv_tcp_t mstTcpSvr;
	std::vector<CTestPasCli*> mvecClis;
};

