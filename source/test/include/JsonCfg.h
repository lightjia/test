#ifndef __CJSONCFG__H_
#define __CJSONCFG__H_
#include "UvFile.h"
class CJsonCfg : public CUvFile
{
public:
	CJsonCfg();
	~CJsonCfg();

protected:
	int OnInit();
	int OnScanDir(uv_fs_t* pFileReq);
	void OnBaseTimer();

private:
	uv_fs_t mstReq;
	uv_dirent_t mstDirent;
};

#endif