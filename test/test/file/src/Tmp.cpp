#include "Tmp.h"
#include "CLogmanager.h"


CTmp::CTmp()
{
    LOG_INFO("New Tmp:%p", this);
}


CTmp::~CTmp()
{
    LOG_INFO("Release Tmp:%p", this);
}
