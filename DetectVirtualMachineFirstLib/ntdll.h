#pragma once
#include "Struct.h"

#pragma comment(lib, "ntdll.lib")

EXTERN_C NTSTATUS NTAPI 
NtQuerySystemInformation(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID               SystemInformation,
	IN ULONG                SystemInformationLength,
	OUT PULONG              ReturnLength OPTIONAL);


EXTERN_C NTSTATUS NTAPI 
SyscallTermMyProc(



	IN HANDLE               ProcessHandle OPTIONAL,
	IN NTSTATUS             ExitStatus);



/*
*

Flush writeback data set from previous instruction to system memory.
 Set memory to 0. This is in WB memory so it will not be in system memory.
Flush the caches but do not write back to system memory. Real hardware will result in loss of previous operation.
 Proper system behaviour will have AL = 1; Hypervisor/emulator that uses WBINVD or does nothing will have AL = 0.

*/