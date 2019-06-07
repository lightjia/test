#pragma once
#include "UvTcpSvr.h"
#include "TestPasCli.h"
#include "UvLoop.h"
#include <vector>
class CTestSvr : public CUvTcpSvr, public CUvLoopCb{
public:
	CTestSvr();
	~CTestSvr();

public:
	int OnAccept(uv_tcp_t* pUvTcp);
	int OnInit();
	int UvCallBack(uv_loop_t* pLoop, void* pData);
	uv_tcp_t* AllocTcpCli();

private:
	CUvLoop* mpMyLoop;
	uv_tcp_t* mpCliTcp;
	int miStep;
	CTestPasCli* mpPasCli;
	uv_tcp_t mstTcpSvr;
	std::vector<CTestPasCli*> mvecClis;
};

