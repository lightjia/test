#ifndef __CUVDIR__H_
#define __CUVDIR__H_
#include "UvFile.h"
class CUvDir : public CUvFile {
public:
    CUvDir();
    ~CUvDir();

protected:
    int OnInit();
    int OnScanDir(uv_fs_t* pFileReq);

private:
    uv_fs_t mstReq;
    uv_dirent_t mstDirent;
};

#endif