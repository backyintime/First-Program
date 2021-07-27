#pragma once

#include <StackWalker.h>
#include<QDebug>

class MyStackWalker : public StackWalker
{
public:
    MyStackWalker() : StackWalker() {}
    std::string GetInfos();
    virtual BOOL SetCallStack(HANDLE                    hThread = GetCurrentThread(),
                              const CONTEXT*            context = NULL,
                              PReadProcessMemoryRoutine readMemoryFunction = NULL,
                              LPVOID pUserData = NULL);
protected:
    static void MyStrCpy(char* szDest, size_t nMaxDestSize, const char* szSrc);
    virtual void OnOutput(LPCSTR szText) {  }
    virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName) {  }
    virtual void OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size,
                              DWORD result, LPCSTR symType, LPCSTR pdbName,
                              ULONGLONG fileVersion) { /*std::cout << "YY";*/}
    virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry);

    virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr) { /*std::cout << "AA";*/ }
private:
    std::string   infos;
    /*[STACKWALK_MAX_NAMELEN];
    size_t maxLen = STACKWALK_MAX_NAMELEN*/;
};

