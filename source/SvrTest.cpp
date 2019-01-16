// SvrTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CLogmanager.h"
#include "JsonCfg.h"
#include "GuidTool.h"

void Hello() {
	LOG_INFO("Hello Jia");
}

int main()
{
	sLog->Init(LOG_TYPE_SCREEN, LOG_LEVEL_MAX, ".");
	for(;;){
		LOG_INFO("Guid:%s", sGuidTool->CreateGuid().c_str());
		sleep_ms(1000);
	}
	CJsonCfg cCfg;
	cCfg.SetUvLoop(uv_default_loop());
	cCfg.Init();
	cCfg.ScanDir("D:/", 0);

	while (1) {
		uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	}
	
    return 0;
}

