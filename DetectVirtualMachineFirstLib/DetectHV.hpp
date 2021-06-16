#pragma once
#include "ntdll.h"
#include <intrin.h>
#include "AlterApi.h"
#include <iostream>




EXTERN_C void BEShit();

EXTERN_C  bool  CheckInd();
EXTERN_C __int64 LBRVirt();
namespace DetectHyp {


#define LODWORD(_qw)    ((DWORD)(_qw))






	inline int GetWindowsBuld()
	{
		return *(DWORD*)0x7FFE026C;  /* KUSER_SHARED_DATA + WindowsBuld		 = 10*/
	}

	inline int GetBuildNumber()
	{
		return 	*(ULONG*)0x07FFE0260;	/*KUSER_SHARED_DATA + NtBuildNumber	   build = 19042*/
	}


	inline bool CpuidIsHyperv()
	{
		
		// Query hypervisor precense using CPUID (EAX=1), BIT 31 in ECX 
		int cpuinf[4] = { 0 };
		__cpuid(cpuinf, 1);
		return ((cpuinf[2] >> 31) & 1);
		
	}

	inline bool KiSyntheticMsrCheck()
	{

		__try
		{
			__readmsr(0x40000000);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return FALSE;
		}

		return TRUE;
	}

	inline  bool   RdtscCpu()
	{
		DWORD tsc1 = 0;
		DWORD tsc2 = 0;
		DWORD avg = 0;
		INT cpuInfo[4] = {};
		for (INT i = 0; i < 10; i++)
			{
				tsc1 = __rdtsc();
				__cpuid(cpuInfo, 0);
				tsc2 = __rdtsc();
				avg += (tsc2 - tsc1);
			}
			avg = avg / 10;
			return (avg < 500 && avg > 25) ? FALSE : TRUE;




	}

	inline bool Rdtscp() {
		


		unsigned int  blabla = 0;
		unsigned int tscp1 = 0;
		unsigned int tscp2 = 0;
		DWORD avg = 0;
		INT cpuid[4] = {};

		for (INT j = 0; j < 10; j++)
		{
			tscp1 = __rdtscp(&blabla);
			__cpuid(cpuid, 0);
			tscp2 = __rdtscp(&blabla);
			avg += tscp2 - tscp1;
			if (avg < 500 && avg > 25)
				return false;  
			else
				avg = 0;
		}
		return true;
		

	}
		

	

	
	inline bool  RdtscHeap()
	{
		ULONGLONG tsc1;
		ULONGLONG tsc2;
		ULONGLONG tsc3;



		for (DWORD i = 0; i < 10; i++)
		{
			tsc1 = __rdtsc();

			GetProcessHeap();

			tsc2 = __rdtsc();

			CloseHandle(0);

			tsc3 = __rdtsc();
			
			if ((LODWORD(tsc3) - LODWORD(tsc2)) / (LODWORD(tsc2) - LODWORD(tsc1)) >= 10)
				return FALSE;
		}



		return TRUE;
	}
	inline bool UmpIsSystemVirtualized() {
		

		unsigned int invalid_leaf = 0x13371337;
		unsigned int valid_leaf = 0x40000000;



		int  InvalidLeafResponse[4] = { 0 ,0,0,0 };
		int ValidLeafResponse[4] = { 0 ,0,0,0 };

		__cpuid(InvalidLeafResponse, invalid_leaf);
		__cpuid(ValidLeafResponse, valid_leaf);

		if ((InvalidLeafResponse[0] != ValidLeafResponse[0]) ||
			(InvalidLeafResponse[1] != ValidLeafResponse[1]) ||
			(InvalidLeafResponse[2] != ValidLeafResponse[2]) ||
			(InvalidLeafResponse[3] != ValidLeafResponse[3]))
			return true;

		return false;
		

	}


	inline int filter(unsigned int code, struct _EXCEPTION_POINTERS* ep, bool& bDetected, int& singleStepCount)
	{
		if (code != EXCEPTION_SINGLE_STEP)
		{
			bDetected = true;
			return EXCEPTION_CONTINUE_SEARCH;
		}

		singleStepCount++;
		if ((size_t)ep->ExceptionRecord->ExceptionAddress != (size_t)BEShit + 11)
		{
			bDetected = true;
			return EXCEPTION_EXECUTE_HANDLER;
		}

		bool bIsRaisedBySingleStep = ep->ContextRecord->Dr6 & (1 << 14);
		bool bIsRaisedByDr0 = ep->ContextRecord->Dr6 & 1;
		if (!bIsRaisedBySingleStep || !bIsRaisedByDr0)
		{
			bDetected = true;
		}
		return EXCEPTION_EXECUTE_HANDLER;
	}


	

	inline bool SehCpuid() 
	{
		
		bool bDetected = 0;
		int singleStepCount = 0;
		CONTEXT ctx{};
		ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
		GetThreadContext(GetCurrentThread(), &ctx);
		ctx.Dr0 = (size_t)BEShit + 11;
		ctx.Dr7 = 1;
		SetThreadContext(GetCurrentThread(), &ctx);
		__try
		{
			BEShit();
		}
		__except (filter(GetExceptionCode(), GetExceptionInformation(), bDetected, singleStepCount))

		{
			if (singleStepCount != 1)
			{
				bDetected = 1;
			}

		}
		return bDetected;
		
		
	}
	inline bool VMExit_xgetbv() {
		UINT64 XCR0 = _xgetbv(0);

		__try {
			// Clear the bit 0 of XCR0 to cause a #GP(0)!
			_xsetbv(0, XCR0 & ~1);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {

			//normal
			return false;
		}
		return true;
	}
	inline bool SidtExcept() {
		__try {
			__sidt(NULL);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
		return true;
	}



	
	inline bool CheckIndv() {
		
		__try {		CheckInd();		}
		__except (EXCEPTION_EXECUTE_HANDLER) 
		{
			return false;
		}
		return true;
	}

	inline bool LBRBadVirtCheck() {
		__try {
		 LBRVirt() 
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
		return true;
	}
	

	

	inline bool  CpuidbyName()
	{
		

		INT CPUInfo[4] = { -1 };
		CHAR szHypervisorVendor[0x40];
		WCHAR* pwszConverted;

		BOOL bResult = FALSE;
		
		
		const TCHAR* szBlacklistedHypervisors[] = {
			(L"KVMKVMKVM\0\0\0"),	/* KVM */
			(L"Microsoft Hv"),		/* Microsoft Hyper-V or Windows Virtual PC */
			(L"VMwareVMware"),		/* VMware */
			(L"XenVMMXenVMM"),		/* Xen */
			(L"prl hyperv  "),		/* Parallels */
			(L"VBoxVBoxVBox"),		/* VirtualBox */
		};

		WORD dwlength = sizeof(szBlacklistedHypervisors) / sizeof(szBlacklistedHypervisors[0]);

		// __cpuid with an InfoType argument of 0 returns the number of
		// valid Ids in CPUInfo[0] and the CPU identification string in
		// the other three array elements. The CPU identification string is
		// not in linear order. The code below arranges the information 
		// in a human readable form.
		__cpuid(CPUInfo, 0x40000000);
		memset(szHypervisorVendor, 0, sizeof(szHypervisorVendor));
		memcpy(szHypervisorVendor, CPUInfo + 1, 12);

		for (int i = 0; i < dwlength; i++)
		{
			pwszConverted = alternat_api::CharToWChar_T(szHypervisorVendor);
			if (pwszConverted) {

				bResult = (wcscmp(pwszConverted, szBlacklistedHypervisors[i]) == 0);

				free(pwszConverted);

				if (bResult)
					return TRUE;
			}
		}
		
			
		return FALSE;
	}




	inline bool SysHypervInform(){
		

		SYSTEM_HYPERVISOR_DETAIL_INFORMATION systInformat{0};
		ULONG retLenth = NULL;

			 NtQuerySystemInformation(
			SystemHypervisorDetailInformation,
			&systInformat,
			sizeof(SYSTEM_HYPERVISOR_DETAIL_INFORMATION), //0x70
			&retLenth
			);


	//	SYSTEM_HYPERVISOR_DETAIL_INFORMATION -> https://www.geoffchappell.com/studies/windows/km/ntoskrnl/api/ex/sysinfo/hypervisor_detail.htm


			 return systInformat.ImplementationLimits.Data[0] != 0	
				 &&  systInformat.HypervisorInterface.Data[0] != 0
				 &&  systInformat.EnlightenmentInfo.Data[0] != 0
				 &&  systInformat.HvVendorAndMaxFunction.Data[0] != 0
				 &&  systInformat.HvVendorAndMaxFunction.Data[1] != 0;
			 


		//This do detect 
		/*systInformat.ImplementationLimits.Data[0] != 0
		SYSTEM_HYPERVISOR_DETAIL_INFORMATION->HV_IMPLEMENTATION_LIMITS->MaxVirtualProcessorCount

		return systInformat.HypervisorInterface.Data[0] != 0;
		SYSTEM_HYPERVISOR_DETAIL_INFORMATION->HV_HYPERVISOR_INTERFACE_INFO->Interface
		
		
		return  systInformat.EnlightenmentInfo.Data[0] != 0;
		SYSTEM_HYPERVISOR_DETAIL_INFORMATION->HV_X64_ENLIGHTENMENT_INFORMATION->bla bla bla
	
		return	systInformat.HvVendorAndMaxFunction.Data[0] != 0 || systInformat.HvVendorAndMaxFunction.Data[1] != 0;
		SYSTEM_HYPERVISOR_DETAIL_INFORMATION->HvVendorAndMaxFunction->Interface ||		SYSTEM_HYPERVISOR_DETAIL_INFORMATION->HvVendorAndMaxFunction->	Reserved1
		
		return systInformat.ImplementationLimits.Data[0] != 0;
		SYSTEM_HYPERVISOR_DETAIL_INFORMATION->HV_IMPLEMENTATION_LIMITS->MaxVirtualProcessorCount
		*/
	
	}
	
}
