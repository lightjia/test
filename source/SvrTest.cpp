// SvrTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CLogmanager.h"
#include "JsonCfg.h"

void Hello() {
	LOG_INFO("Hello Jia");
}

int main()
{
	sLog->Init(LOG_TYPE_SCREEN, LOG_LEVEL_MAX, ".");
	CJsonCfg cCfg;
	cCfg.SetUvLoop(uv_default_loop());
	cCfg.Init();
	cCfg.ScanDir("D:/", 0);

	while (1) {
		uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	}
	
    return 0;
}

