This repository covers various techniques and methods I write while conducting research into infoleaks, these are for leaking various Windows kernel addresses on Windows 10 1607, 1703, 1809, and 1909. 

Blog post that goes along with this - https://fullpwnops.com/Windows-10-kaslr-infoleak/

### Windows 10 1607 - (Anniversary Update)

- **DesktopHeap (TEB.Win32ClientInfo) kernel information leakage**

The following information leakage proof-of-concept works on various Windows versions, from Windows 7 till Windows 10 1603, where it has now been mitigated in 2016 via the 1703 update.

This Windows kernel address leakage proof-of-concept demonstrates how the user-mode mapped DesktopHeap on Windows 1607 x64 bit can be used to leak various kernel addresses via undocumented kernel data structures and undocumented members.

![desktop heap leakage](https://github.com/FULLSHADE/LEAKYDRIPPER/blob/master/images/DesktopHeapLeak.png)

### Resources

- [1] [https://reactos.org/wiki/Techwiki:Win32k](https://reactos.org/wiki/Techwiki:Win32k)
- [2] [https://fullpwnops.com/Windows-10-kaslr-infoleak/](https://fullpwnops.com/Windows-10-kaslr-infoleak/)

----

### Windows 10 1703 - (Creators Update)

With the Windows 10 1703 update in 2016, `ulClientDelta` from `Win32ClientInfo` has been removed, successfully mitigating the previously demonstrated information leak. 

### Windows 10 (all/most versions)

- **EnumDeviceDrivers kernel information leakage**

This is the classic and easiest technique for bypassing KASRL using the EnumDeviceDrivers winAPI function to get the base address of ntoskrnl, this technique works on pretty much every Windows version. But it requires at least medium-integrity execution. 

![desktop heap leakage](https://github.com/FULLSHADE/LEAKYDRIPPER/blob/master/images/EnumDeviceDrivers.PNG)
