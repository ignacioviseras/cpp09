#include "PmergeMe.hpp"

static bool validateArgs(const std::string &argv) {
	if (argv.empty())
		return false;
	for (size_t i = 0; i < argv.size(); i++) {
		if (!isdigit(argv[i]))
			return false;
	}
	return true;
	
}

int main(int argc, char** argv) {
	
	if (argc < 2) {
		std::cerr << "Error need more params" << std::endl;
		return 1;
	}

	PmergeMe pmerge;
	for (int i = 1; i < argc; i++)
	{
		if (!validateArgs(argv[i])) {
			std::cerr << "invlaid argument " << argv[i] << std::endl;
			return 1;
		}
		try {
			pmerge.addNumber(std::atoi(argv[i]));
		}
		catch(const std::exception& e){
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
	std::cout << "Before: ";	
	pmerge.printBefore(argv);
	
	clock_t start = clock();
	pmerge.initVector();
	double tVec = (double)(clock() - start) / CLOCKS_PER_SEC * 1000;
	start = clock();
	pmerge.initDeque();
	double tDeq = (double)(clock() - start) / CLOCKS_PER_SEC * 1000;

	std::cout << "After: ";
	pmerge.printAfter();
	std::cout << "Time to process a range of " << argc - 1
			  << " elements with std::vector : " << tVec << " ms" << std::endl;
	std::cout << "Time to process a range of " << argc - 1
			  << " elements with std::deque : " << tDeq << " ms" << std::endl;
	return 0;
}