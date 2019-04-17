#ifndef __LOGMANAGER__H_
#define __LOGMANAGER__H_
#include "singleton.h"
#include "util.h"
#include "UvMutex.h"
#include "UvThread.h"
#include "UvCond.h"
#include "MemOper.h"
#include <queue>
#include <string>
#include <vector>
#include <map>

enum LogType{ LOG_TYPE_SCREEN = 0, LOG_TYPE_FILE, LOG_TYPE_TEE, LOG_TYPE_MAX};
enum LogLevel{
	LOG_LEVEL_ERR = 0,
	LOG_LEVEL_DBG,
	LOG_LEVEL_FUNCTION,
	LOG_LEVEL_INFO,
	LOG_LEVEL_BLANK,
	LOG_LEVEL_MAX
};

#define MAX_PER_LOGFILE_SIZE 500*1024*1024	//������־�ļ��Ĵ�СΪ500M
#define MAX_PER_LINE_LOG	1024 * 6	//һ����־��󻺴�
#define MAX_PER_LOG_ITEM_CACHE_SIZE 1024*100 //������־����߻���

typedef void(*log_cb)(int iLevel, const char *pData);

#pragma pack(1)
struct tagLogItem
{
	int iLevel;
    char* pLog;
    unsigned long iUse;
    unsigned long iTotal;
};
#pragma pack()

class CLog : public CSingleton<CLog>, public CUvThread, public CMemOper
{
	SINGLE_CLASS_INITIAL(CLog);

public:
	int Init(int iType, int iLevel, const char* szDir, log_cb pLogCb=NULL);
	~CLog();
	void AddLogItem(int iLevel, const char *format, ...);
	int StopLog();
	int SetLogType(int iType);
	int SetLogLevel(int iLevel);
	int SetLogPath(const char* pPath);

protected:
    int OnThreadRun();

private:
	int Check();
	FILE* GetFile();
    int SetLogFile(FILE* pFile);
	int PrintItem(tagLogItem* pLogItem);
    void WriteLog(tagLogItem* pLogItem, FILE* pFile);

private:
	int miType;
	int miLevel;
	unsigned long mlCount;
	bool mbInit;
	std::string mstrDir;
	FILE* mpFile;
    CUvMutex mcConfMutex;
	CUvMutex mcQueLogItemsMutex;
    std::queue<tagLogItem*> mQueLogItems;
    unsigned int miCurrentLogItemNum;
    std::map<int, std::vector<tagLogItem*>*> mMapFreeLogItems;
    CUvCond mcCond;
    log_cb mpLogCb;
};

#define sLog CLog::Instance()

#define LOG_ERR(fmt, ...) sLog->AddLogItem(LOG_LEVEL_ERR, "[ERROR](%s:%s:%d)[Thread:%u] " fmt, __FILE__, __FUNCTION__, __LINE__, (unsigned int)get_thread_id_self(), ##__VA_ARGS__)
#define LOG_DBG(fmt, ...) sLog->AddLogItem(LOG_LEVEL_DBG, "[DEBUG](%s:%s:%d)[Thread:%u] " fmt, __FILE__, __FUNCTION__, __LINE__, (unsigned int)get_thread_id_self(), ##__VA_ARGS__)
#define LOG_FUNCTION(fmt, ...) sLog->AddLogItem(LOG_LEVEL_FUNCTION, "[FUNCTION](%s)[Thread:%u] " fmt, __FUNCTION__, (unsigned int)get_thread_id_self(), ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) sLog->AddLogItem(LOG_LEVEL_INFO, "[Thread:%u] " fmt, (unsigned int)get_thread_id_self(), ##__VA_ARGS__)
#define LOG_BLANK(fmt, ...) sLog->AddLogItem(LOG_LEVEL_BLANK, fmt, ##__VA_ARGS__)

#define ASSERT(expr) do{if (!(expr)){LOG_ERR("assert \"%s\" failed", #expr);}}while(0)
#define ASSERT_RET(expr) do{if (!(expr)){LOG_ERR("assert \"%s\" failed", #expr); return ; }}while(0)
#define ASSERT_RET_VALUE(expr, retval) do{if (!(expr)){LOG_ERR("assert \"%s\" failed", #expr); return retval; }}while(0)

#define ASSERT_ERR_MSG(expr, fmt, ...) \
do \
{ \
if (!(expr)) \
{ \
	LOG_ERR("assert \"%s\", msg:" fmt, #expr, ##__VA_ARGS__); \
} \
} while (0);

#define ASSERT_ERR_MSG_RET(expr, retval, fmt, ...) \
do \
{ \
if (!(expr)) \
{ \
	LOG_ERR("assert \"%s\", msg:" fmt, #expr, ##__VA_ARGS__); \
	return retval; \
} \
} while (0);

#endif