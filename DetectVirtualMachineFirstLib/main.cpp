
#include "DetectHV.hpp"




int main() {
	
	

	
	std::cout << "Rdtsc + cpuid ->\t" << DetectHyp::RdtscCpu() << '\n';
	std::cout << "Rdtscp  + cpuid ->\t" << DetectHyp::Rdtscp() << '\n';
	std::cout << "Rdtsc  with GetHeap & CloseHandle ->\t" << DetectHyp::RdtscHeap() << '\n';
	std::cout << "SYSTEM_HYPERVISOR_DETAIL_INFORMATION ->\t" << DetectHyp::SysHypervInform() << '\n';
	std::cout << "Exit VM with xgetbv ->\t" << DetectHyp::VMExit_xgetbv() << '\n';
	std::cout << "Check virt sidt ->\t" << DetectHyp::SidtExcept() << '\n';
	std::cout << "Check virt indv ->\t" << DetectHyp::CheckIndv() << '\n';
	std::cout << "Check virt LBR ->\t" << DetectHyp::LBRBadVirtCheck() << '\n';
	std::cout << "Detect hyp by cpuid & name ->\t" << DetectHyp::CpuidbyName() << '\n';
	std::cout << "Cpuid is hyperv ->\t" << DetectHyp::CpuidIsHyperv() << '\n';
	std::cout << "Mistake hyp cpuid ->\t" << DetectHyp::SehCpuid() << '\n';
	std::cout << "readmsr  0x40000000 ->\t" <<   DetectHyp::KiSyntheticMsrCheck() << '\n';
	std::cout << "Compare cpuid list ->\t" << DetectHyp::UmpIsSystemVirtualized() << '\n';

	
		 



	std::cin.get();
	system("pause");
}