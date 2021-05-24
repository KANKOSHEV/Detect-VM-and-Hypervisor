
#include "DetectHV.hpp"




int main() {
	
	
	std::cout << "Windows Buld->\t" << DetectHyp::GetWindowsBuld() << '\n';
	std::cout << "Buld number ->\t" << DetectHyp::GetBuildNumber() << '\n';
	std::cout << "Rdtsc with cpuid ->\t" << DetectHyp::RdtscCpu() << '\n'; 
	std::cout << "Rdtsc with GetHeap ->\t" << DetectHyp::RdtscHeap() << '\n'; 
	std::cout << "SYSTEM_HYPERVISOR_DETAIL_INFORMATION all check ->\t" << DetectHyp::SysHypervInform() << '\n';
	std::cout << "Check xgetbv ->\t" << DetectHyp::VMExitxgetbv()<< '\n';
	std::cout << "Cpuid is Hyp ->\t" << DetectHyp::CpuidIsHyperv() << '\n';
	std::cout << "Shit BE ->\t" << DetectHyp::DetectHypBySetThreadCpuid() << '\n';
	std::cout << "KiSyntheticMsrCheck ->\t" << DetectHyp::KiSyntheticMsrCheck() << '\n';
   std::cout << "UmpIsSystemVirtualized ->\t" << DetectHyp::UmpIsSystemVirtualized() << '\n';

	std::cin.get();
	system("pause");
}