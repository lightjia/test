#include "UvDir.h"

CUvDir::CUvDir(){
}

CUvDir::~CUvDir(){
}

int CUvDir::OnInit() {
    mpFsReq = &mstReq;
    return StartBaseTimer(2000, 2000);
}

int CUvDir::OnScanDir(uv_fs_t* pFileReq) {
    LOG_INFO("result:%d %s", uv_fs_get_result(pFileReq), uv_fs_get_path(pFileReq));
    if (uv_fs_get_result(pFileReq) > 0) {
        uv_fs_t* pCurReq = pFileReq;
        while (uv_fs_scandir_next(pCurReq, &mstDirent) == 0) {
            LOG_INFO("dir:%d %s", mstDirent.type, mstDirent.name);
            if (mstDirent.type == UV_DIRENT_DIR) {
                std::string strdir = uv_fs_get_path(pFileReq);
                strdir = strdir + "/" + mstDirent.name;
                uv_fs_t *pReq = (uv_fs_t*)do_malloc(sizeof(uv_fs_t));
                mpFsReq = pReq;
                ScanDir(strdir.c_str(), 0);
            }
        }
    }
    return 0;
}