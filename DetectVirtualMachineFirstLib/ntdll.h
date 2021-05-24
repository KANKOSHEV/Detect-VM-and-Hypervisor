#pragma once
#include "Struct.h"

#pragma comment(lib, "ntdll.lib")

EXTERN_C NTSTATUS NTAPI
NtQuerySystemInformation(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID               SystemInformation,
	IN ULONG                SystemInformationLength,
	OUT PULONG              ReturnLength OPTIONAL);