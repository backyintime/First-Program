#include "MyStackWalker.h"

std::string MyStackWalker::GetInfos()
{
    return infos;
}

BOOL MyStackWalker::SetCallStack(HANDLE hThread, const CONTEXT *context, PReadProcessMemoryRoutine readMemoryFunction, LPVOID pUserData)
{
    return true;
}


void MyStackWalker::MyStrCpy(char* szDest, size_t nMaxDestSize, const char* szSrc)
{
    if (nMaxDestSize <= 0)
        return;
    strncpy_s(szDest, nMaxDestSize, szSrc, _TRUNCATE);
    szDest[nMaxDestSize - 1] = 0;
}

void MyStackWalker::OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry)
{
    CHAR   buffer[STACKWALK_MAX_NAMELEN];
    size_t maxLen = STACKWALK_MAX_NAMELEN;
#if _MSC_VER >= 1400
    maxLen = _TRUNCATE;
#endif
    if ((eType != lastEntry) && (entry.offset != 0))
    {
        _snprintf_s(buffer, maxLen, "%s (%d): %s\n", entry.lineFileName, entry.lineNumber, entry.name);
        buffer[STACKWALK_MAX_NAMELEN - 1] = 0;
        infos +=buffer;
    }
}
